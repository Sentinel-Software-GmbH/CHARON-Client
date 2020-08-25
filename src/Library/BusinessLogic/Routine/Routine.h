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
 * Provides functions to transmit data to and from the server.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
#ifndef UDS_ROUTINE_H_
#define UDS_ROUTINE_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void UDS_ROUTINE_routineControl(uint8_t routineCommand, uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint8_t routineControlOptionsLength);


#ifdef __cplusplus
}
#endif


#endif /* UDS_ROUTINE_H_ */
 