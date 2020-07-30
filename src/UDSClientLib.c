/****************************************************
 *  UDSClientLib.c                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class UDSClientLib       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "UDSClientLib.h"
#include "DiagnosticCommunicationManager.h"
#include "DataTransmitter.h"
#include "StoredDataTransmitter.h"
#include "InputOutputController.h"
#include "Routine.h"
#include "UploadDownload.h"
#include "ComLogic/SessionAndTransportManager.h"

#ifndef TEST
    #include "DataModels/PendingObject.h"
#endif

void UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface *security, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    STM_Init(com, timer, security, rxBuffer, rxBufferLength);
}

UDS_Client_Error_t UDS_Client_Task(void) {
    return STM_cyclic();
}
