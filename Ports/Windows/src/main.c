/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 ${Author}
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
 * @addtogroup Window Port
 * @{
 * @file
 * Brief Description.
 * main.c
 * Detailed Description.
 * main
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include "UDSClientLib.h"
#include "config.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdarg.h>

/* Imports *******************************************************************/

extern void pipe_init(void);

extern TimerInterface timer1;
extern ComInterface wincom1;

/* Constants *****************************************************************/

/* Macros ********************************************************************/

#define RX_BUFFER_LENGTH 4096
uint8_t rxBuffer[RX_BUFFER_LENGTH];

#define str(x) #x
#define xstr(x) str(x)

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

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
       UDS_DCM_AccessTimingParameter(0xFFFF, 0xFFFF, printMessage);
    uds_wait();
    UDS_DCM_ClearResponseOnEvents(printMessage);
    uds_wait();
    UDS_DCM_CommunicationControl(UDS_ComCtrl_enableRxAndTx, UDS_Com_normalCommunicationMessages, 0x00, 0x0000, printMessage);
    uds_wait();
       UDS_DCM_ControlDTCSetting(0x01, (uint8_t[]){0x01, 0x02, 0x03, 0x04}, 4, printMessage);
    uds_wait();
    UDS_DCM_DiagnosticSessionControl(UDS_Session_Default, printMessage);
    uds_wait();
    UDS_DCM_ECUReset(UDS_SoftReset, printMessage);
    uds_wait();
    UDS_DCM_GetActiveResponseEvents(printMessage);
    uds_wait();
    UDS_DCM_LinkControl_withFixedParameter(UDS_Baud_PC9600, printMessage);
    uds_wait();
    UDS_DCM_LinkControl_WithSpecificParameter(9600, printMessage);
    uds_wait();
    UDS_DCM_ResponseOnChangeOfDataIdentifier(false, 0x04, 0x0001, SID_DiagnosticSessionControl, NULL, 0, printMessage, printMessage);
    uds_wait();
       UDS_DCM_ResponseOnComparisonOfValues(false, 0x03, 0x0001, CompLogic_LessThan, 0xFFFF, 0x0A, false, 0x02, 0x0001, SID_DiagnosticSessionControl, 0x0001, printMessage, printMessage);
    uds_wait();
    UDS_DCM_ResponseOnDTCStatusChange(false, 0x03, 0xFF, SID_DiagnosticSessionControl, NULL, 0, printMessage, printMessage);
    uds_wait();
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
       pipe_init();
       UDS_Client_Init(&wincom1, &timer1, NULL, rxBuffer, RX_BUFFER_LENGTH);
    DCM();
       exit(0);
}
/* Private Function **********************************************************/


/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
