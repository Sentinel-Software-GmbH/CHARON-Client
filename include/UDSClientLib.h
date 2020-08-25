/****************************************************
 *  UDSClientLib.h                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class UDSClientLib       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_)
#define EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_


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


#endif /*!defined(EA_CAE719C6_0CEB_4c4b_ADB7_E1E052BA52FE__INCLUDED_)*/
 