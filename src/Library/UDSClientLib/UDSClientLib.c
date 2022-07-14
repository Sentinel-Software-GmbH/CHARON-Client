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
 *  Created on: Wed Jul 29 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup Facade
 * @{
 * @file
 * Includes a user friendly representation of the fixed values to adjust the speed.
 * 
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#include "UDSClientLib.h"
#include "SessionAndTransportManager.h"

void UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    STM_Init(com, timer, security, rxBuffer, rxBufferLength);
}

UDS_Client_Error_t UDS_Client_Task(void) {
    return STM_cyclic();
}
