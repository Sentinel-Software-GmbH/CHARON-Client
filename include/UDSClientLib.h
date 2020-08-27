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
 * Created on: Mon Aug 24 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup Facade
 * @{
 * @file
 * Facade Header to include everything the user needs in one header.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

#ifndef UDS_CLIENT_LIBRARY_H_
#define UDS_CLIENT_LIBRARY_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"

#include "DataModels/ErrorCode.h"
#include "DataModels/Session.h"
#include "DataModels/MemoryDefinition.h"
#include "DataModels/DataDefinition.h"
#include "DataModels/BaudRates.h"
#include "DataModels/CommunicationControl.h"
#include "DataModels/ComparisonLogic.h"
#include "DataModels/ResetTypes.h"
#include "DataModels/SID.h"
#include "DataModels/TimerRates.h"
#include "Interfaces/ComInterface.h"
#include "Interfaces/TimerInterface.h"
#include "Interfaces/CallbackInterface.h"
#include "Interfaces/SecurityInterface.h"

#include <stdbool.h>
#include <stdint.h>

/** @brief Provides an universal entry function to initialize all Submodules
 * @param com An already initialized implementation of a UDS Communication Interface.
 * @param timer An already initialized implementation of a UDS TimerInterface.
 * @param security An already initialized implementation of the Security Layer Interface.
 * @param rxBuffer Pointer to the rxBuffer provided by the user.
 */
void UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength);

/** @brief Cyclic Task that receives Messages and handles KeepAlives.
 * @returns The last error code that has occured. See @ref UDS_Client_Error_t.
 */ 
UDS_Client_Error_t UDS_Client_Task(void);

#include "BusinessLogic/DataTransmitter/DataTransmitter.h"
#include "BusinessLogic/DCM/DiagnosticCommunicationManager.h"
#include "BusinessLogic/DTC/StoredDataTransmitter.h"
#include "BusinessLogic/IOControl/InputOutputController.h"
#include "BusinessLogic/Routine/Routine.h"
#include "BusinessLogic/UploadDownload/UploadDownload.h"

#ifdef __cplusplus
}
#endif

#endif /* UDS_CLIENT_LIBRARY_H_ */
 