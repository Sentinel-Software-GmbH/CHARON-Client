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
 * @defgroup ComLogic
 * @{
 * @file $Filename$.h
 * Brief Description.
 * Detailed Description
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

typedef enum UDS_Baudrate_public {
    UDS_BAUDRATE_RESERVED = 0x00,
    PC9600Baud = 0x01,
    PC19200Baud = 0x02,
    PC38400Baud = 0x03,
    PC57600Baud = 0x04,
    PC115200Baud = 0x05,
    CAN125000Baud = 0x10,
    CAN250000Baud = 0x11,
    CAN500000Baud = 0x12,
    CAN1000000Baud = 0x13,
    ProgrammingSetup = 0x20,
    _UDS_Baudrate_amount
} UDS_Baudrate_t;

/* Interfaces ****************************************************************/

#endif /* UDS_BAUD_RATE_H_ */

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
