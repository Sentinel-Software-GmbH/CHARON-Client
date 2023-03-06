/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 Steven Inácio
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup ComLogic
 * @{
 * @file
 * This Session and Transport Manager handles all communication to the Communication Interface.
 * It also handles the KeepAlive in a non-default Session.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

/* Includes ******************************************************************/

#include "SessionAndTransportManager.h"
#include "SID.h"
#include "Session.h"
#include "config.h"
#include <stddef.h>

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/** @brief Macro for convenient configuration of suppress bit. */
#define SUPPRESS_BIT 0x80

/* Types *********************************************************************/

/* Variables *****************************************************************/

/** @brief save location of @ref ComInterface to use later. */
static ComInterface *s_com;

/** @brief save location of @ref TimerInterface to use later. */
static TimerInterface *s_timer;

/** @todo: SecureInterface */
/** @brief save location of @ref SecurityInterface to use later. */
static SecurityInterface *s_security;

/** @brief save location of @ref UDS_Session_t to use later. */
static UDS_Session_t session;

/** @brief save location of session_timeout to use later. */
static uint32_t session_timeout;

/** @brief save location of s_timeout to use later. */
static uint32_t s_timeout;

/** @brief save location of @ref PendingObject to use later. */
static struct PendingObject pending;

/** @brief save location of PendingObject asyncPending to use later. */
static struct PendingObject asyncPending[MAX_ASYNC_MESSAGES];

/** @brief save location of asyncPendingLength to use later. */
static uint8_t asyncPendingLength;

/** @brief save location of s_suppressPosResponse to use later. */
static bool s_suppressPosResponse;

/** @brief save location of secured_transmit to use later. */
static bool secured_transmit;

/** @brief save location of rx buffer to use later. */
static uint8_t *rx;

/** @brief save location of rxLength and currentRxLength to use later. */
static uint32_t rxLength, currentRxLength;

/** @brief save location of currentRxLength to use later. */
static uint32_t currentRxLength;

/** @brief save location of KeepAlivelastSend to use later. */
static uint32_t KeepAlivelastSend = -1;

/** @brief save location of startingPService to use later. */
static bool startingPService = false;

/** @brief save location of stoppingPService to use later. */
static bool stoppingPService = false;

/** @brief save location of periodicServiceActive to use later. */
static bool periodicServiceActive = false;

/* Private Function Definitions **********************************************/

/** @brief This function is used to renew timeout if Tester present was so server. */
static bool KeepAlive(void);

/** @brief This function makes use of the ComInterface to send messages to server.
 * 
 * @param buffer Contains message send to server.
 * @param length Size of buffer in bytes.
 * @return Status if success or failure.
 */
static bool send(uint8_t *buffer, uint32_t length);

/** @brief This function makes use of the ComInterface to receive messages from server.
 * 
 * @param buffer 
 * @param length 
 * @return int32_t 
 */
static int32_t receive(uint8_t *buffer, uint32_t length);

/** @brief This function is used to reset pending SID and send callback. */
static void resetPendingObject();

/** @brief This function is used to  reset none default session to default session along with the timings.*/
static void resetSession();

/** @brief Function is used to get difference between two provided timestamps.
 * 
 * @param start Parameter to start measurement. 
 * @return The difference between two provided timestamps.
 */
static int64_t diffNow(uint32_t start);

/** @brief This function is used to find the current pending SID out of pending list.
 * 
 * @param sid Service ID  @ref SID_t
 * @return Number of pending services. 
 */
static int8_t findSID(SID_t sid);

/** @brief Function is used to check if server response and reset pending SID if needed.*/
static UDS_Client_Error_t handlePendingNothingReceived();

/** @brief Functions checks if server sends negative response reset pending SID. 
 * 
 * @param readBytes Number of received bytes.
 * @return @ref UDS_Client_Error_t 
 */
static UDS_Client_Error_t handleNegativeResponse(int32_t readBytes);

/** @brief Functions checks if server sends positive response reset pending SID.
 * 
 * @param readBytes 
 * @return @ref UDS_Client_Error_t 
 */
static UDS_Client_Error_t handlePositiveResponse(int32_t readBytes);

/* Interfaces  ***************************************************************/

void STM_Init(const ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t *const rxBuffer, uint32_t rxBufferLength)
{
    s_com = com;
    s_timer = timer;
    s_security = security;
    rx = rxBuffer;
    rxLength = rxBufferLength;
    currentRxLength = 0;
    session_timeout = NON_DEFAULT_SESSION_TIMEOUT;
    resetSession();
    resetPendingObject();
    asyncPendingLength = 0;
}

bool STM_Deploy(uint8_t *data, uint32_t length, UDS_callback callback, bool suppressPositiveResponse)
{
    UDS_MUTEX_LOCK();
    bool startPS = false;
    if (data[0] == SID_ReadDataByPeriodicIdentifier)
    {
        if ((data[1] & 0x7F) == 0x04 && periodicServiceActive)
        {
            if((length < 3) || (asyncPendingLength == 0u))
            {
                stoppingPService = true;
            }
        }
        else
            startPS = true;
    }
    if (pending.SID != 0x00 && !stoppingPService)
    {
        UDS_MUTEX_UNLOCK();
        pending.SID = 0x00; /** this helped to send request more often*/
        if (callback != NULL)
            callback(E_Busy, NULL, 0);
        return false;
    }

    s_suppressPosResponse = suppressPositiveResponse;
    if (suppressPositiveResponse)
    {
        data[1] = data[1] | SUPPRESS_BIT;
    }
    if (secured_transmit)
    {
        /** @todo: Manipulate Data to send over SecureDataTransmit Service. */ 
    }
    uint8_t tmpSid = data[0];
    if (send(data, length))
    {
        startingPService = startPS;
        pending.callback = callback;
        pending.SID = tmpSid;
        s_timeout = s_timer->getTime() + session.p2;
        UDS_MUTEX_UNLOCK();
        return true;
    }
    else if (stoppingPService)
        stoppingPService = false;
    else if (startingPService)
        startingPService = false;
    UDS_MUTEX_UNLOCK();
    return false;
}

bool STM_AsyncDeploy(SID_t sid, UDS_callback callback)
{
    UDS_MUTEX_LOCK();
    if (asyncPendingLength >= MAX_ASYNC_MESSAGES)
    {
        UDS_MUTEX_UNLOCK();
        return false;
    }
    asyncPending[asyncPendingLength].SID = sid;
    asyncPending[asyncPendingLength].callback = callback;
    asyncPendingLength++;
    UDS_MUTEX_UNLOCK();
    return true;
}

bool STM_RemoveAsync(SID_t sid)
{
    uint8_t idx;
    // If it's not found, it can't be removed
    UDS_MUTEX_LOCK();
    if ((idx = findSID(sid)) == -1)
        return false;
    // Shift following objects to fill to left.
    for (uint8_t i = idx; i < asyncPendingLength - 1; i++)
    {
        asyncPending[idx].SID = asyncPending[idx + 1].SID;
        asyncPending[idx].callback = asyncPending[idx + 1].callback;
    }
    // Decrease Length
    asyncPendingLength--;
    UDS_MUTEX_UNLOCK();
    return true;
}

void STM_ClearAsync()
{
    asyncPendingLength = 0;
}

UDS_Client_Error_t STM_cyclic(void)
{
    UDS_Client_Error_t retVal = E_OK;
    int32_t readBytes = 0;
    // send KeepAlive if we're not in Default Session.
    if (session.session != UDS_Session_Default)
    {
        KeepAlive();
    }
    // Check if there is some work to do.
    UDS_MUTEX_LOCK();
    if ((readBytes = receive(rx, rxLength)) > 0)
    {
        if (periodicServiceActive && !stoppingPService)
        {
            if (pending.callback != NULL)
                pending.callback(E_OK, rx, readBytes);
        }
        else
        {
            SID_t sid = rx[0];
            int8_t idx;
            if (sid == SID_NEGATIVE_RESPONSE)
            {
                retVal = E_NegativeResponse;
                sid = rx[1];
            }
            else
            {
                sid -= 0x40;
            }
            if (secured_transmit)
            {
                /** @todo: Manipulate received data to decrypt through security interface. */
            }
            // If/ElseIf/Else is faster depending on platform.
            // Since we are platform independent we use the statistically fastest method.
            if (pending.SID == sid)
            {
                // if it's a Negative Response
                if (E_NegativeResponse == retVal)
                {
                    retVal = handleNegativeResponse(readBytes);
                }
                else
                {
                    retVal = handlePositiveResponse(readBytes);
                }
            }
            else if (SID_TesterPresent == sid)
            {
                // NOTE: Not regulated in the ISO Standard.
                UDS_LOG_WARNING("Tester Present received negative Answer, resetting Session...");
                resetSession();
            }
            else if ((idx = findSID(sid)) >= 0)
            {
                if (asyncPending[idx].callback != NULL)
                    asyncPending[idx].callback(retVal, rx, readBytes);
            }
            else
            {
                UDS_LOG_WARNING("Received unexpected answer.");
                retVal = E_Unexpected;
            }
        }
    }
    else if (periodicServiceActive)
    {
        retVal = E_Pending;
    }
    else if (pending.SID != 0x00)
    {
        retVal = handlePendingNothingReceived();
    }
    UDS_MUTEX_UNLOCK();
    return retVal;
}

bool STM_LinkControl(uint32_t speed)
{
    return s_com->setSpeed(speed);
}

bool STM_SpeedIsAdjustable()
{
    return s_com->speedIsAdjustable;
}

void STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout)
{
    UDS_MUTEX_LOCK();
    if (session_type != 0x00)
    {
        session.session = session_type;
    }
    session.p2 = p2_timeout;
    session.p2_star = p2_star_timeout;
    UDS_MUTEX_UNLOCK();
}

void STM_SetSessionTimeout(uint32_t timeout)
{
    /** @todo finish this  STM_SetSessionTimeout */
}

/* Private Function **********************************************************/

UDS_Client_Error_t handlePendingNothingReceived()
{
    UDS_Client_Error_t retVal = E_OK;
    if (!s_suppressPosResponse)
    {
        retVal = E_Pending;
    }
    if (diffNow(s_timeout) >= 0)
    {
        if (s_suppressPosResponse)
        {
            retVal = E_OK;
        }
        else
        {
            retVal = E_NotResponding;
        }
        if (pending.callback != NULL)
            pending.callback(retVal, NULL, 0);
        resetPendingObject();
    }
    return retVal;
}

UDS_Client_Error_t handleNegativeResponse(int32_t readBytes)
{
    if (NRC_responsePending == rx[2])
    {
        s_timeout = s_timer->getTime() + session.p2_star;
        return E_Pending;
    }
    else
    {
        if (pending.callback != NULL)
            pending.callback(E_NegativeResponse, rx, readBytes);
        if (!stoppingPService)
            resetPendingObject();
        startingPService = stoppingPService = false;
        return E_NegativeResponse;
    }
}

UDS_Client_Error_t handlePositiveResponse(int32_t readBytes)
{
    if (pending.callback != NULL)
        pending.callback(E_OK, rx, readBytes);
    if (startingPService)
        periodicServiceActive = true;
    if (stoppingPService)
        periodicServiceActive = false;
    if (!startingPService)
        resetPendingObject();
    startingPService = stoppingPService = false;
    /** @todo add return value but not the correct one needs to be checked again! */
    return E_OK;
}

bool send(uint8_t *buffer, uint32_t length)
{
    int32_t sentBytes = 0, currentRetVal;
    do
    {
        currentRetVal = s_com->send(&buffer[sentBytes], length - sentBytes);
        if (currentRetVal < 0)
        {
            // ERROR
            UDS_LOG_ERROR("Could not send full message");
            return false;
        }
        else
        {
            sentBytes += currentRetVal;
        }
    } while (sentBytes < length);
    return true;
}

int32_t receive(uint8_t *buffer, uint32_t length)
{
    return s_com->receive(buffer, length);
}

bool KeepAlive()
{
    UDS_MUTEX_LOCK();
    if (diffNow(KeepAlivelastSend) >= session_timeout)
    {
        UDS_LOG_INFO("Sending KeepAlive.");
        if (send((uint8_t[]){SID_TesterPresent, 0x00 | SUPPRESS_BIT}, 2))
        {
            KeepAlivelastSend = s_timer->getTime();
            UDS_LOG_INFO("New Timeout: %u", KeepAlivelastSend);
        }
        else
        {
            UDS_LOG_WARNING("Error sending KeepAlive.");
            UDS_MUTEX_UNLOCK();
            return false;
        }
    }
    UDS_MUTEX_UNLOCK()
    return true;
}

void resetPendingObject(void)
{
    pending.SID = 0x00;
    pending.callback = NULL;
}

void resetSession(void)
{
    session.session = UDS_Session_Default;
    session.p2 = P2_DEFAULT;
    session.p2_star = P2_STAR_DEFAULT;
}

int8_t findSID(SID_t sid)
{
    for (uint8_t i = 0; i < asyncPendingLength; i++)
    {
        if (asyncPending[i].SID == sid)
            return i;
    }
    return -1;
}

int64_t diffNow(uint32_t start)
{
    return s_timer->diffTime(start, s_timer->getTime());
}

#ifdef TEST
ComInterface *STM_getComInterface(void)
{
    return s_com;
}
TimerInterface *STM_getTimerInterface(void) { return s_timer; }
UDS_Session_t STM_getCurrentSession(void)
{
    return session;
}
uint8_t STM_getCurrentSID(void) { return pending.SID; }
void STM_setCurrentSession(UDS_SessionType_t sType, uint16_t p2, uint16_t p2_star)
{
    session.session = sType;
    session.p2 = p2;
    session.p2_star = p2_star;
}
void STM_setCurrentSID(uint8_t sid) { pending.SID = sid; }

void STM_setStartPeriodicService(bool val) { startingPService = val; }

void STM_setStopPeriodicService(bool val) { stoppingPService = val; }

void STM_setPeriodicServiceActive(bool val) { periodicServiceActive = val; }

bool STM_getStartPeriodicService() { return startingPService; }

bool STM_getStopPeriodicService() { return stoppingPService; }

bool STM_getPeriodicServiceActive() { return periodicServiceActive; }

#endif
