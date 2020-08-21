/**
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
 * @defgroup DataModels
 * @{
 * @file ResetTypes.h
 * Includes a representation of all reset functions used by the function UDS_DCM_ECUReset().
 * 
 * Check ISO 14229-1 Chapter 9.3 Table 34
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_RESET_H_
#define UDS_RESET_H_

/** @brief How the Server should Reset on an ECU Reset Request. */
typedef enum UDS_Reset_Type_public {
    UDS_Reset_Reserved00 = 0x00,                /**< ISO Reserved*/
    UDS_HardReset = 0x01,                       /**< Force a Hard Reset on the Server. */
    UDS_KeyOffOnReset = 0x02,                   /**< Simulate an Ignition Off and On Event. */
    UDS_SoftReset = 0x03,                       /**< Softreset the ECU. */
    UDS_enableRapidPowerShutDown = 0x04,        /**< Enable a rapid Shutdown on ECUs that support this. */
    UDS_disableRapidPowerShutDown = 0x05,       /**< Disable a rapid Shutdown on ECUs that support this. */
} UDS_Reset_t;

#endif /* UDS_RESET_H_ */
