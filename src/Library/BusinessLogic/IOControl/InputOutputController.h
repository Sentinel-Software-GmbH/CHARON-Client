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
 * @defgroup BusinessLogic
 * @{
 * @file
 * Implementation of the Input Output Controller Functional Unit.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

#ifndef UDS_INPUT_OUTPUT_CONTROLLER_H_
#define UDS_INPUT_OUTPUT_CONTROLLER_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "Interfaces/CallbackInterface.h"

/** @brief Return the Control of an IO DataIdentifier back to the ECU
 * @req R21 Request to Control IO of the server.
 * @param dataIdentifier A data identifier that references an in- or output value.
 * @param controlMask List of Bit Masks of all Data Identifier Values that you want to change. see ISO 14229-1 Table 353
 * @param controlMaskLength Length of the Control Mask list.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_IO_ReturnControlToECU(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback);

/** @brief Return the IO DataIdentifier back to it's default Values.
 * @req R21 Request to Control IO of the server.
 * @param dataIdentifier A data identifier that references an in- or output value.
 * @param controlMask List of Bit Masks of all Data Identifier Values that you want to change. see ISO 14229-1 Table 353
 * @param controlMaskLength Length of the Control Mask list.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_IO_ResetToDefault(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback);

/** @brief Freeze the current state of an io data identifier.
 * @req R21 Request to Control IO of the server.
 * @param dataIdentifier A data identifier that references an in- or output value.
 * @param controlMask List of Bit Masks of all Data Identifier Values that you want to change. see ISO 14229-1 Table 353
 * @param controlMaskLength Length of the Control Mask list.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_IO_FreezeCurrentState(uint16_t dataIdentifier, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback);

/** @brief Adjust the io data identifier data.
 * @req R21 Request to Control IO of the server.
 * @param dataIdentifier A data identifier that references an in- or output value.
 * @param adjustedData A Bytearray of the adjusted data behind a data identifier reference you want to change.
 * @param adjustedDataLength Length of the adjustedData byte array.
 * @param controlMask List of Bit Masks of all Data Identifier Values that you want to change. see ISO 14229-1 Table 353
 * @param controlMaskLength Length of the Control Mask list.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_IO_ShortTermAdjustment(uint16_t dataIdentifier, uint8_t *adjustedData, uint32_t adjustedDataLength, uint8_t *controlMask, uint32_t controlMaskLength, UDS_callback callback);

#ifdef __cplusplus
}
#endif


#endif /* UDS_INPUT_OUTPUT_CONTROLLER_H_ */
 