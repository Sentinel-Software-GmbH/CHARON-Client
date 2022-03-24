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
 */
 /**
  * @addtogroup UDS_Client
  * @{
  * @addtogroup BusinessLogic
  * @{
  * @file
  * Implementation of the Routine Functional Unit.
  *
  * $Id:  $
  * $URL:  $
  * @}
  * @}
  */

  /* INCLUDE */

#include <string.h>
#include "Routine.h"
#include "DataModels/SID.h"
#include "ComLogic/SessionAndTransportManager.h"
#include "config.h"

#if USE_STATIC_BUFFER == 1
extern uint8_t message[STATIC_BUFFER_SIZE];
#endif

/* Private Function Definitions */

static bool commonRoutine(uint8_t command, uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback);

/* Interface Functions */

bool UDS_ROUTINE_startRoutine(uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback)
{
	return commonRoutine(0x01, routineIdentifier, routineControlOptionRecord, routineControlOptionsLength, callback);
}
bool UDS_ROUTINE_stopRoutine(uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback)
{
	return commonRoutine(0x02, routineIdentifier, routineControlOptionRecord, routineControlOptionsLength, callback);
}
bool UDS_ROUTINE_requestRoutineResults(uint16_t routineIdentifier, UDS_callback callback)
{
	return commonRoutine(0x03, routineIdentifier, NULL, 0, callback);
}

/* Private Functions */

static bool commonRoutine(uint8_t command, uint16_t routineIdentifier, uint8_t* routineControlOptionRecord, uint32_t routineControlOptionsLength, UDS_callback callback)
{
#if USE_STATIC_BUFFER == 0
	uint8_t message[4 + routineControlOptionsLength];
#else
	if (4 + routineControlOptionsLength > STATIC_BUFFER_SIZE) {
		if(callback != NULL)
			callback(E_MessageTooLong, NULL, 0);
		return false;
	}
#endif
	message[0] = SID_RoutineControl;
	message[1] = command;
	message[2] = (uint8_t)(routineIdentifier >> 8);
	message[3] = (uint8_t)routineIdentifier;
	if (routineControlOptionsLength > 0) {
		memcpy(&message[4], routineControlOptionRecord, routineControlOptionsLength);
	}
	return STM_Deploy(message, 4 + routineControlOptionsLength, callback, false);
}