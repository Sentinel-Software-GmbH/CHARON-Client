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

void UDS_IO_InputOutputControlByIdentifier(uint16_t dataIdentifier, uint8_t inputOutputControlParameter, uint8_t* controlStates, uint8_t controlStatesLength, uint8_t* controlMasks, uint8_t controlMasksLength);


#ifdef __cplusplus
}
#endif


#endif /* UDS_INPUT_OUTPUT_CONTROLLER_H_ */
 