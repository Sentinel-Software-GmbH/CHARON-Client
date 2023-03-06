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
 * 
 *  Created on: 16.07.2018
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup ComLogic Communication Logic Modules
 * @{
 * @file
 * Provides functions to transmit data to and from the server.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

#ifndef UDS_SESSION_AND_TRANSPORT_MANAGER_H_
#define UDS_SESSION_AND_TRANSPORT_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ******************************************************************/

#include "ComInterface.h"
#include "TimerInterface.h"
#include "SecurityInterface.h"
#include "CallbackInterface.h"
#include "Session.h"
#include "ErrorCode.h"
#include "SID.h"

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** @brief  */
struct PendingObject {
    uint8_t SID;            /**< Service ID @ref SID_t. */
    UDS_callback callback;  /**< callback function for PendingObject @ref UDS_callback. */
};

/* Interfaces ****************************************************************/

/** @brief Initialize STM Module.
 * 
 * @param com Provides Functions to communicate through the user implemented connection driver @ref ComInterface.
 * @param timer represents the implementation of a System Timer @ref TimerInterface.
 * @param security Provides Security functions to encrypt and decrypt byte arrays @ref SecurityInterface.
 * @param rxBuffer provides receive Buffer for messages. 
 * @param rxLength length of rxbuffer in bytes.
 */
void STM_Init(const ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxLength);

/** @brief Handles and deploys the messages send to Server.
 * 
 * @param data data send to Server (e.q. SID).
 * @param length length of the data in bytes.
 * @param callback Provides Security functions to encrypt and decrypt byte arrays @ref UDS_callback. 
 * @param suppressPositiveResponse modifier to suppress positive response message from server. 
 * @return status if deploy of message was successful.
 */
bool STM_Deploy(uint8_t *data, uint32_t length, UDS_callback callback, bool suppressPositiveResponse);

/** @brief Handles and deploys the messages send asynchronous to Server.
 * 
 * @param sid Service ID @ref SID_t.
 * @param callback Provides Security functions to encrypt and decrypt byte arrays @ref UDS_callback.
 * @return status if deploy of message was successful.
 */
bool STM_AsyncDeploy(SID_t sid, UDS_callback callback);

/** @brief Removes SIDs from pending message queue.
 * 
 * @param sid Service ID @ref SID_t.
 * @return result if removing sid was successful.
 */
bool STM_RemoveAsync(SID_t sid);

/** @brief Ceeps current session alive, checks and receives messages if available. 
 * 
 * @return UDS_Client_Error_t @ref UDS_Client_Error_t
 */
UDS_Client_Error_t STM_cyclic(void);

/**
 * @brief Function to adjust the baudrate.
 * 
 * @param speed desired baudrate to set
 * @return Success or failure as boolean.
 */
bool STM_LinkControl(uint32_t speed);

/** @brief Checks if baudrate is adjustable.
 * 
 * @return True if adjustable.
 */
bool STM_SpeedIsAdjustable(void);

/** @brief Function to change current ISO specified Session on the Server.
 * 
 * @param session_type session to set @ref UDS_SessionType_t. 
 * @param p2_timeout  Timeout for the initial answer.
 * @param p2_star_timeout Timeout for the extended answer.
 */
void STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout);

/** @brief Change default timeout value for current session.
 * 
 * @param timeout Timeout for the initial answer.
 */
void STM_SetSessionTimeout(uint32_t timeout);

/** @brief Reset content of pending list. */
void STM_ClearAsync();

#ifdef TEST
    ComInterface* STM_getComInterface(void);
    TimerInterface* STM_getTimerInterface(void);
    uint8_t STM_getCurrentSID(void);
    UDS_Session_t STM_getCurrentSession(void);
    void STM_setCurrentSID(uint8_t sid);
    void STM_setStartPeriodicService(bool val);
    void STM_setStopPeriodicService(bool val);
    void STM_setPeriodicServiceActive(bool val);
    bool STM_getStartPeriodicService();
    bool STM_getStopPeriodicService();
    bool STM_getPeriodicServiceActive();
#endif

#ifdef __cplusplus
}
#endif


#endif /* UDS_SESSION_AND_TRANSPORT_MANAGER_H_ */
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/