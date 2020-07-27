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

static uint8_t *rx;

bool UDS_Client_Init(ComInterface *com, TimerInterface *timer, SecurityInterface_t *security, uint8_t * const rxBuffer, uint32_t rxBufferLength) {
    bool retVal = DCM_Init(security);
    retVal &= STM_Init(com, timer, rxBuffer, rxBufferLength);
    return retVal;
}

UDS_Client_Error_t UDS_Client_Task(void) {
    return STM_cyclic();
}

bool UDS_Client_switchSession(UDS_SessionType_t session, uint16_t p2, uint16_t p2_star, UDS_callback callback) {
    return DiagnosticSessionControl(session, p2, p2_star, callback);
}
