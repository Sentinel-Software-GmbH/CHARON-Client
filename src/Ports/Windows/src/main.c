#include "UDSClientLib.h"
#include "config.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>

#define str(x) #x
#define xstr(x) str(x)

extern void pipe_init(void);

extern TimerInterface timer1;
extern ComInterface wincom1;

#define RX_BUFFER_LENGTH 4096
uint8_t rxBuffer[RX_BUFFER_LENGTH];

void printMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length) {
    if(error != E_OK) {
        UDS_LOG_WARNING("Got Error response %s (0x%02x)", ErrorCode_STRING[error], error);
    }
    if(receive != NULL) {
        printf("[UDS Client] CALLBACK: 0x");
        for (int i = 0; i < receive_length; i++) {
            printf("%02x", receive[i]);
        }
        printf("\n");    
    }
    return;
}

void uds_wait() {
    int counter = 0;
    while(E_Pending == UDS_Client_Task()) {
        if(counter == 100) {
            UDS_LOG_ERROR("Timeout.");
            break;
        }
        Sleep(100);
        counter++;
    }
    return;
}


void Setup() {
    //UDS_DCM_ECUReset(UDS_SoftReset, printMessage);
}

void DCM() {
    Setup();
    UDS_LOG_INFO("Set Access Timing Parameter to 0xFFFF and 0xFFFF");
    UDS_DCM_AccessTimingParameter(0xFFFF, 0xFFFF, printMessage);
    uds_wait();
    UDS_LOG_INFO("Clearing ResponseOnEvents");
    UDS_DCM_ClearResponseOnEvents(printMessage);
    uds_wait();
    UDS_LOG_INFO("Setting %s (0x%02x) on %s (0x%02x) with subnet 0x00 and Node IDs of 0x0000", xstr(ComCtrl_enableRxAndTx), ComCtrl_enableRxAndTx, xstr(Com_normalCommunicationMessages), Com_normalCommunicationMessages);
    UDS_DCM_CommunicationControl(ComCtrl_enableRxAndTx, Com_normalCommunicationMessages, 0x00, 0x0000, printMessage);
    uds_wait();
    UDS_LOG_INFO("Enabling DTCs 0x01, 0x02, 0x03 and 0x04");
    UDS_DCM_ControlDTCSetting(0x01, (uint8_t[]){0x01, 0x02, 0x03, 0x04}, 4, printMessage);
    uds_wait();
    UDS_LOG_INFO("Setting Session to %s (0x%02x)", xstr(UDS_Session_Default), UDS_Session_Default);
    UDS_DCM_DiagnosticSessionControl(UDS_Session_Default, printMessage);
    uds_wait();
    UDS_LOG_INFO("Resetting with Resettype %s (0x%02x)", xstr(UDS_SoftReset), UDS_SoftReset);
    UDS_DCM_ECUReset(UDS_SoftReset, printMessage);
    uds_wait();
    UDS_LOG_INFO("Get All Active Response Events");
    UDS_DCM_GetActiveResponseEvents(printMessage);
    uds_wait();
    UDS_LOG_INFO("Verify Link Control with Fixed Parameter %s (0x%02x)", xstr(PC9600Baud), PC9600Baud);
    UDS_DCM_LinkControl_verifyWithFixedParameter(PC9600Baud, printMessage);
    uds_wait();
    UDS_LOG_INFO("Verify Link Control with Specific %d Baud. 0x%04x", 9600, 9600);
    UDS_DCM_LinkControl_verifyWithSpecificParameter(9600, printMessage);
    uds_wait();
    UDS_LOG_INFO("Trying to get a Response on Change of DID.");
    UDS_DCM_ResponseOnChangeOfDataIdentifier(false, 0x04, 0x0001, SID_DiagnosticSessionControl, NULL, 0, printMessage, printMessage);
    uds_wait();
    UDS_LOG_INFO("Trying to get a Response when DID 0x0001 is LessThan 0xFFFF with a 10\% Hysterisis");
    UDS_DCM_ResponseOnComparisonOfValues(false, 0x03, 0x0001, LessThan, 0xFFFF, 0x0A, false, 0x02, 0x0001, SID_DiagnosticSessionControl, 0x0001, printMessage, printMessage);
    uds_wait();
    UDS_LOG_INFO("Trying to get a Response on DTC Status Change on DTC Mask 0xFF.");
    UDS_DCM_ResponseOnDTCStatusChange(false, 0x03, 0xFF, SID_DiagnosticSessionControl, NULL, 0, printMessage, printMessage);
    uds_wait();
    UDS_LOG_INFO("Trying to get a Security Seed on Funtion 0x03");
    UDS_DCM_SecurityAccess(0x03, (uint8_t[]){0x00, 0x00, 0x00, 0x00}, 4, printMessage);
    uds_wait();
}

void DTC() {

}

void IOControl() {

}

void UploadDownload() {

}

void Routine() {

}

void DataTransmit() {

}


int main(void) {
    UDS_LOG_INFO("Init pipe.");
    pipe_init();
    UDS_LOG_INFO("Init Client.");
    UDS_Client_Init(&wincom1, &timer1, NULL, rxBuffer, RX_BUFFER_LENGTH);
    DCM();
    UDS_LOG_INFO("Exitting...");
    exit(0);
}