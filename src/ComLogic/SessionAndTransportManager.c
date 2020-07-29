/****************************************************
 *  SessionAndTransportManager.c
 *  Created on: 16-Jul-2020 09:29:59
 *  Implementation of the Class SessionAndTransportManager
 *  Original author: Steven Inacio
 ****************************************************/

/* Includes ******************************************************************/

#include "SessionAndTransportManager.h"
#include "session.h"
#include "DataModels/SID.h"
#include <stddef.h>
#include "config.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

#define SUPPRESS_BIT 0x80


/* Macros ********************************************************************/

/* Types *********************************************************************/



/* Variables *****************************************************************/

static ComInterface *s_com;
static TimerInterface *s_timer;

// TODO: SecureInterface
static SecurityInterface *s_security;

static UDS_Session_t session;
static uint32_t session_timeout;

static uint32_t s_timeout;

static struct PendingObject pending;

static struct PendingObject asyncPending[MAX_ASYNC_MESSAGES];

static uint8_t asyncPendingLength;

static bool s_suppressPosResponse;

static bool secured_transmit;

static uint8_t *rx;
static uint32_t rxLength, currentRxLength;

static uint32_t KeepAlivelastSend = -1;
/* Private Function Definitions **********************************************/

UDS_Client_Error_t KeepAlive(void);

bool send(uint8_t* buffer, uint32_t length);

int32_t receive(uint8_t* buffer, uint32_t length);

void resetPendingObject();

void resetSession();

int32_t diffNow(uint32_t start);

int findSID(SID_t sid);

/* Interfaces  ***************************************************************/

void STM_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    s_com = com;
    s_timer = timer;
    s_security = security;
    rx = rxBuffer;
    rxLength = rxBufferLength;
    currentRxLength = 0;
    session_timeout = DEFAULT_SESSION_TIMEOUT;
    resetSession();
    resetPendingObject();
    asyncPendingLength = 0;
    return true;
}

bool STM_Deploy(uint8_t *data, uint32_t length, UDS_callback callback, bool suppressPositiveResponse) {
    if(pending.SID != 0x00) {
        return false;
    }
    s_suppressPosResponse = suppressPositiveResponse;
    if (suppressPositiveResponse) {
        data[1] = data[1] | SUPPRESS_BIT;
    }
    if(secured_transmit) {
        // TODO: Manipulate Data to send over SecureDataTransmit Service.
    }
    if (send(data, length) == length) {
        pending.callback = callback;
        pending.SID = data[0];
        s_timeout = s_timer->getTime() + session.p2;
        return true;
    }
    return false;
}

bool STM_AsyncDeploy(SID_t sid, UDS_callback callback) {
    if (asyncPendingLength >= MAX_ASYNC_MESSAGES) return false;
    asyncPending[asyncPendingLength].SID = sid;
    asyncPending[asyncPendingLength].callback = callback;
    asyncPendingLength++;
    return true;
}

bool STM_RemoveAsync(SID_t sid) {
    int idx;
    // If it's not found, it can't be removed
    if((idx = findSID(sid)) == -1) return false;
    // Shift following objects to fill to left.
    for (int i = idx; i < asyncPendingLength - 1; i++) {
        asyncPending[idx].SID = asyncPending[idx + 1].SID;
        asyncPending[idx].callback = asyncPending[idx + 1].callback;
    }
    // Decrease Length
    asyncPendingLength--;
    return true;
}

UDS_Client_Error_t STM_cyclic(void) {
    UDS_Client_Error_t retVal = E_OK;
    int32_t readBytes = 0;
    // send KeepAlive if we're not in Default Session.
    if (session.session != UDS_Session_Default)
    {
        KeepAlive();
    }
    // Check if there is some work to do.
    if((readBytes = receive(rx, rxLength)) > 0) {
        SID_t sid = rx[0];
        int idx;
        if (sid == SID_NEGATIVE_RESPONSE) {
            retVal = E_NegativeResponse;
            sid = rx[1];
        }
        else
            if(secured_transmit) {
                // TODO: Manipulate received data to decrypt through security interface.
            }
            sid -= 0x40;
        // If/ElseIf/Else is faster depending on platform.
        // Since we are platform independent we use the statistically fastest method.
        if (pending.SID == sid) {
            // if it's a Negative Response
            if(E_NegativeResponse == retVal && NRC_responsePending == rx[2]) {
                retVal = E_Pending;
                s_timeout = s_timer->getTime() + session.p2_star;
            }
            else if(pending.callback != NULL)
                pending.callback(retVal, rx, readBytes);
        }
        else if(SID_TesterPresent == sid) {
            // NOTE: Not regulated in the ISO Standard.
            resetSession();
        }
        else if (idx = findSID(sid) >= 0) {
            if (asyncPending[idx].callback != NULL)
                asyncPending[idx].callback(retVal, rx, readBytes);
        }
        else {
            // Unexpected receive
        }
    }
    else if(pending.SID != 0x00) {
        if(!s_suppressPosResponse) {
            retVal = E_Pending;
        }
        if(diffNow(s_timeout) >= 0) {
            if(s_suppressPosResponse) {
                retVal = E_OK;
            } else {
                retVal = E_NotResponding;
            }
            if(pending.callback != NULL)
                pending.callback(retVal, NULL, 0);
            resetPendingObject();
        }
    }
    return retVal;
}

bool STM_LinkControl(uint32_t speed) {
    return s_com->setSpeed(speed);
}

bool STM_SpeedIsAdjustable() {
    return s_com->speedIsAdjustable;
}

bool STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout) {
    if (session_type != 0x00) {
        session.session = session_type;
    } 
    session.p2 = p2_timeout;
    session.p2_star = p2_star_timeout;
}

/* Private Function **********************************************************/

bool send(uint8_t* buffer, uint32_t length) {
    int32_t sentBytes = 0, currentRetVal = 0;
    do {
        currentRetVal = s_com->send(buffer[sentBytes], length - sentBytes);
        if(currentRetVal < 0) {
            // ERROR
            return false;
        }
        else {
            sentBytes += currentRetVal;
        }
    } while (sentBytes < length);
    return true;
}

int32_t receive(uint8_t* buffer, uint32_t length) {
    return s_com->receive(buffer, length);
}

UDS_Client_Error_t KeepAlive() {
    if (diffNow(KeepAlivelastSend) >= session_timeout) {
        if(send((uint8_t[]){ SID_TesterPresent, 0x00 | SUPPRESS_BIT}, 2) == 2) {
            KeepAlivelastSend = s_timer->getTime();
        }
    }
}

void resetPendingObject(void) {
    pending.SID = 0x00;
    pending.callback = NULL;
}

void resetSession(void) {
    session.session = UDS_Session_Default;
    session.p2 = P2_DEFAULT;
    session.p2_star = P2_STAR_DEFAULT;
}

int findSID(SID_t sid) {
    for(int i = 0; i < asyncPendingLength; i++) {
        if(asyncPending[i].SID == sid) return i;
    }
    return -1;
}

int32_t diffNow(uint32_t start) {
    return s_timer->diffTime(start, s_timer->getTime());
}

#ifdef TEST
    ComInterface* STM_getComInterface(void) { return s_com; }
    TimerInterface* STM_getTimerInterface(void) { return s_timer; }
    UDS_Session_t STM_getCurrentSession(void) {
        return session;
    }
    uint8_t STM_getCurrentSID(void) { return pending.SID; }
    void STM_setCurrentSession(UDS_SessionType_t sType, uint16_t p2, uint16_t p2_star) {
        session.session = sType;
        session.p2 = p2;
        session.p2_star = p2_star;
    }
    void STM_setCurrentSID(uint8_t sid) { pending.SID = sid; }
#endif

/* if (pending.SID != 0x00)
    {
        if (currentRxLength = receive(rx, rxLength) > 0)
        {
            if(rx[0] == NRC_responsePending) 
            { // Got response pending.
                retVal = E_Pending;
                s_timeout = s_timer->getTime() + session.p2_star;
            }
            else if (!(pending.SID + 0x40 == rx[0]) || SID_NEGATIVE_RESPONSE == rx[0]) 
            { // Check for negative responses.
                retVal = E_NegativeResponse;
                if(pending.SID == rx[1])
                {
                    if(pending.callback != NULL)
                        pending.callback(retVal, rx, currentRxLength);
                    resetPendingObject();
                }
                else
                {
                    // confused screeching
                    // TODO: Handle unexepected Negative responses. 
                }
            }
            else
            { // Everything fine.
                retVal = E_OK;
                if(pending.callback != NULL)
                    pending.callback(retVal, rx, currentRxLength);
                resetPendingObject();
            }
        }
        else
        { // receive Failed
            if(diffNow(s_timeout) >= 0)
            {
                retVal = E_NotResponding;
            }
            else {
                retVal = E_Pending;
            }
        }
    }
    else
    { // Nothing to do.
        retVal = E_OK;
    }

bool SecuredDataTransmission(uint8_t *data, uint32_t length, UDS_callback callback)
{
	if(SecurityModule == NULL) {
		return false;
	}
	bool retVal;
	uint8_t message[1 + length];
	message[0] = SID_SecuredDataTransmission;
	memcpy(&message[1], SecurityModule->encrypt(data, length), length);
	if ((retVal = STM_Deploy(message, 1 + length, SecureData_callback, false)) != false)
		DSC_user_callback = callback;
	return retVal;
}
*/