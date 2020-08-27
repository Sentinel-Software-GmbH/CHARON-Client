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
 * @defgroup ComLogic
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

#include "Interfaces/ComInterface.h"
#include "Interfaces/TimerInterface.h"
#include "Interfaces/SecurityInterface.h"
#include "Interfaces/CallbackInterface.h"
#include "DataModels/Session.h"
#include "DataModels/ErrorCode.h"
#include "DataModels/SID.h"

struct PendingObject {
    uint8_t SID;
    UDS_callback callback;
};

void STM_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxLength);

bool STM_Deploy(uint8_t *data, uint32_t length, UDS_callback callback, bool suppressPositiveResponse);

bool STM_AsyncDeploy(SID_t sid, UDS_callback callback);

bool STM_RemoveAsync(SID_t sid);

UDS_Client_Error_t STM_cyclic(void);

bool STM_LinkControl(uint32_t speed);

bool STM_SpeedIsAdjustable(void);

void STM_SetSession(UDS_SessionType_t session_type, uint16_t p2_timeout, uint16_t p2_star_timeout);

void STM_SetSessionTimeout(uint32_t timeout);

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
 