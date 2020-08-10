/****************************************************
 *  UDSClientLib.c                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class UDSClientLib       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "UDSClientLib.h"
#include "BusinessLogic/DCM/DiagnosticCommunicationManager.h"
#include "BusinessLogic/DataTransmitter/DataTransmitter.h"
#include "BusinessLogic//DTC/StoredDataTransmitter.h"
#include "BusinessLogic/IOControl/InputOutputController.h"
#include "BusinessLogic/Routine/Routine.h"
#include "BusinessLogic/UploadDownload/UploadDownload.h"
#include "ComLogic/SessionAndTransportManager.h"

void UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    STM_Init(com, timer, security, rxBuffer, rxBufferLength);
}

UDS_Client_Error_t UDS_Client_Task(void) {
    return STM_cyclic();
}
