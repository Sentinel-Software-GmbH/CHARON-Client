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

#include "DataModels/ErrorCode.h"
#include "DataModels/Session.h"
#include "DataModels/MemoryDefinition.h"
#include "DataModels/DataDefinition.h"
#include "DataModels/ResponseCode.h"
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


// UDSClient setzt Stuff Pending Object an mit Usr_CB.
// Pending Object kann Receive_CB haben
// Wenn kein Receive_CB verfügbar, dann Default_CB => check if positive response
// Wenn Pending Object bereits existiert, dann Busy zurückgeben.

void UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength);

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
 