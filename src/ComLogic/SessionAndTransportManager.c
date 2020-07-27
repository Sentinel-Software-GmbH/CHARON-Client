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

/* Imports *******************************************************************/

/* Constants *****************************************************************/

#define SUPPRESS_BIT 0x80
// These times are from the CHARON UDS Server implementation
#define P2_DEFAULT 100U
#define P2_STAR_DEFAULT 300U
#define DEFAULT_SESSION_TIMEOUT 1000U

/* Macros ********************************************************************/

/* Types *********************************************************************/

#ifndef UDS_callback
    typedef void(*UDS_callback)(UDS_Client_Error_t errorCode, uint8_t* buffer, uint32_t length);
#endif

struct PendingObject {
    uint8_t SID;
    UDS_callback callback;
};

/* Variables *****************************************************************/

static ComInterface *s_com;
static TimerInterface *s_timer;

static UDS_Session_t session;
static uint32_t session_timeout;

static uint32_t s_timeout;

static struct PendingObject pending;

static bool s_suppressPosResponse;

static uint8_t *rx;
static uint32_t rxLength, currentRxLength;

/* Private Function Definitions **********************************************/

UDS_Client_Error_t KeepAlive(void);

bool send(uint8_t* buffer, uint32_t length);

uint32_t receive(uint8_t* buffer, uint32_t length);

void resetPendingObject();

void resetSession();

int32_t diffNow(uint32_t start);

/* Interfaces  ***************************************************************/

bool STM_Init(ComInterface *com, TimerInterface *timer, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    if(!com->init()) {
        return false;
    }
    s_com = com;
    s_timer = timer;
    rx = rxBuffer;
    rxLength = rxBufferLength;
    currentRxLength = 0;
    session_timeout = DEFAULT_SESSION_TIMEOUT;
    resetSession();
    resetPendingObject();
    return true;
}

bool STM_Deploy(uint8_t *data, uint32_t length, void(*callback)(UDS_Client_Error_t error, uint8_t* buffer, uint32_t length), bool suppressPositiveResponse) {
    s_suppressPosResponse = suppressPositiveResponse;
    if (suppressPositiveResponse) {
        data[1] = data[1] | SUPPRESS_BIT;
    }
    if (send(data, length)) {
        pending.callback = callback;
        pending.SID = data[0];
        s_timeout = s_timer->getTime() + session.p2;
        return true;
    }
    return false;
}

// TODO: Handle Negative Responses for KeepAlive.
UDS_Client_Error_t STM_cyclic(void) {
    UDS_Client_Error_t retVal;
    if (session.session != UDS_Session_Default)
    {
        KeepAlive();
    }
    if (pending.SID != 0x00)
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
    return retVal;
}

void STM_LinkControl() {}

bool STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout) {
    if (session_type != 0x00) {
        session.session = session_type;
    } 
    session.p2 = p2_timeout;
    session.p2_star = p2_star_timeout;
}

/* Private Function **********************************************************/

bool send(uint8_t* buffer, uint32_t length) {
    return s_com->send(buffer, length);
}

uint32_t receive(uint8_t* buffer, uint32_t length) {
    return s_com->receive(buffer, length);
}

UDS_Client_Error_t KeepAlive() {
    static uint32_t lastSend = -1;
    if (diffNow(lastSend) >= session_timeout) {
        if(send((uint8_t[]){ SID_TesterPresent, 0x00 | SUPPRESS_BIT}, 2)) {
            lastSend = s_timer->getTime();
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