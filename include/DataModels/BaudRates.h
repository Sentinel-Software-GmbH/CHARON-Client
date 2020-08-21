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
 * @file BaudRates.h
 * Includes a user friendly representation of the fixed values to adjust the speed.
 * 
 * Check ISO 14229-1 Table B.3 Page 335
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

#ifndef UDS_BAUD_RATE_H_
#define UDS_BAUD_RATE_H_

/* Includes ******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/** @brief ISO-specified fixed Baudrates.
 * Used to tell the UDS-Server at what speed the client wants to communicate.
 */
typedef enum UDS_Baudrate_public {
    UDS_BAUDRATE_RESERVED = 0x00,           /**< ISO Reserved */
    UDS_Baud_PC9600 = 0x01,                 /**< UART 9600 Bd */
    UDS_Baud_PC19200 = 0x02,                /**< UART 19200 Bd */
    UDS_Baud_PC38400 = 0x03,                /**< UART 38400 Bd */
    UDS_Baud_PC57600 = 0x04,                /**< UART 57600 Bd*/
    UDS_Baud_PC115200 = 0x05,               /**< UART 115200 Bd*/
    UDS_Baud_CAN125000 = 0x10,              /**< CAN 0.125 MBd*/
    UDS_Baud_CAN250000 = 0x11,              /**< CAN 0.25 MBd */
    UDS_Baud_CAN500000 = 0x12,              /**< CAN 0.5 MBd */
    UDS_Baud_CAN1000000 = 0x13,             /**< CAN 1.0 MBd */
    UDS_Baud_ProgrammingSetup = 0x20,       /**< Vendor specific Programming Baudrate. */
#ifndef DOXY_SKIP
    _UDS_Baudrate_amount
#endif
} UDS_Baudrate_t;

/* Interfaces ****************************************************************/

#endif /* UDS_BAUD_RATE_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
