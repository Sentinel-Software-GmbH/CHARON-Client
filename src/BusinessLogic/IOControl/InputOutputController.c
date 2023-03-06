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
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup BusinessLogic
 * @{
 * @file
 * Implementation of the Input Output Controller Functional Unit.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 *****************************************************************************/

/* Includes ******************************************************************/

#include "InputOutputController.h"
#include "SID.h"
#include <string.h>
#include "SessionAndTransportManager.h"

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Private Function Definitions */

/** @brief This callback function is used to put together messages send to server for Input Output Controller Functional Unit.
 * 
 * @param command Is the Input Output Control Parameter.
 * @param dataIdentifier A data identifier that references an in - or output value.
 * @param controlMask List of Bit Masks of all Data Identifier Values that you want to change. see ISO 14229-1 Table 353
 * @param controlMaskLength Length of the Control Mask list.
 * @param callback  A user provided callback function that gets executed when a Server response was received or an error has occurred @ref UDS_callback.
 * @return Status if message was successful.
 */
static bool commonControl(uint8_t command, uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback);

/* Interface Functions */

bool UDS_IO_ReturnControlToECU(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback)
{
    return commonControl(0x00, dataIdentifier, controlMask, controlMaskLength, callback);
}

bool UDS_IO_ResetToDefault(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback)
{
    return commonControl(0x01, dataIdentifier, controlMask, controlMaskLength, callback);
}

bool UDS_IO_FreezeCurrentState(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback)
{
    return commonControl(0x02, dataIdentifier, controlMask, controlMaskLength, callback);
}

bool UDS_IO_ShortTermAdjustment(uint16_t dataIdentifier, uint8_t *adjustedData, uint32_t adjustedDataLength, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback)
{
    uint8_t message[4 + adjustedDataLength + controlMaskLength];
    message[0] = SID_InputOutputControlByIdentifier;
    message[1] = dataIdentifier >> 8;
    message[2] = dataIdentifier;
    message[3] = 0x03;
    if (adjustedDataLength > 0) {
        memcpy(&message[4], adjustedData, adjustedDataLength);
    }
    if (controlMaskLength > 0) {
        memcpy(&message[4 + adjustedDataLength], controlMask, controlMaskLength);
    }
    return STM_Deploy(message, 4 + adjustedDataLength + controlMaskLength, callback, false);
}

/* Private Functions */

static bool commonControl(uint8_t command, uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback)
{
    uint8_t message[4 + controlMaskLength];
    message[0] = SID_InputOutputControlByIdentifier;
    message[1] = dataIdentifier >> 8;
    message[2] = dataIdentifier;
    message[3] = command;
    if (controlMaskLength > 0) {
        memcpy(&message[4], controlMask, controlMaskLength);
    }
    return STM_Deploy(message, 4 + controlMaskLength, callback, false);
}
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
