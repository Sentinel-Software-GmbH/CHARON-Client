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
#include <stdbool.h>
#include "Interfaces/CallbackInterface.h"
#include "compiler.h"

/** @brief Start routine in the server.
 * @param routineIdentifier Routine Identifier. see ISO 14229-1 Annex F Tabelle F.1
 * @param routineControlOptionRecord Routine entry option parameters, which optionally specify start conditions of the routine.
 * @param routineControlOptionsLength Size in bytes of the routineControlOptionRecord.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_ROUTINE_startRoutine(uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback);

/** @brief Stop routine in the server.
 * @param routineIdentifier Routine Identifier. see ISO 14229-1 Annex F Tabelle F.1
 * @param routineControlOptionRecord Routine exit option parameters, which optionally specify stop conditions of the routine.
 * @param routineControlOptionsLength Size in bytes of the routineControlOptionRecord.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_ROUTINE_stopRoutine(uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback);

/** @brief Request the Routine Results.
 * @param routineIdentifier Routine Identifier. see ISO 14229-1 Annex F Tabelle F.1
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
public bool UDS_ROUTINE_requestRoutineResults(uint16_t routineIdentifier, UDS_callback callback);

#ifdef __cplusplus
}
#endif


#endif /* UDS_ROUTINE_H_ */
 