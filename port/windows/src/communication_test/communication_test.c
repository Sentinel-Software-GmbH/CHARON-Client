/*
 *  Sentinel Software GmbH
 *  Copyright (C) 2023 Rene Mutscheller
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
 * @addtogroup WindowsPort Windows Port
 * @{
 * @file communication_test.c
 * Functions for testing communication and debugging.
 * 
 * 
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
#include "DiagnosticCommunicationManager.h"
#include "StoredDataTransmitter.h"

/* Imports *******************************************************************/


/* Constants *****************************************************************/

/* Function Definitions ******************************************************/
/** @brief Declare external member of @ref TimerInterface class to access system time functionality. */
extern TimerInterface timer1;
/** @brief Declare external member of @ref ComInterface class to access driver connection functionality.  */
extern const ComInterface wincom1;

/* Constants *****************************************************************/

/* Macros ********************************************************************/
/** @brief Macro for convenient configuration of rx buffer size.*/
#define RX_BUFFER_LENGTH 4096
/** @brief  */
uint8_t rxBuffer[RX_BUFFER_LENGTH];
/** @brief macro for convenient usage of logger functions. */
#define str(x) #x
/** @brief macro for convenient usage of logger functions. */
#define xstr(x) str(x)

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Private Function Definitions **********************************************/

/** @brief This function is used to print error messages received via server response or user callback function.
 * 
 * @param error Error response received from server @ref UDS_Client_Error_t.
 * @param receive Buffer containing received message from callback function.
 * @param receive_length Size of buffer contend in bytes.
 */
static void printMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length);

/** @brief This function is used to to check if UDS_Client_Task is still pending and raise an timeout Error if needed. */
static void uds_wait();


/* Interfaces  ***************************************************************/

/** @brief This function is used to prepare and setup environment for trouble free client usage.*/
void Setup() 
{
    //UDS_DCM_ECUReset(UDS_SoftReset, printMessage);
}

/** @brief This Function calls all implemented and integrated Diagnostic Communication Manager functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
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

/** @brief This Function calls alls implemented and integrated Diagnostic Trouble Code functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void DTC() 
{
    // get current DTC counter
    UDS_DTC_ReportNumberOfDTCByStatusMask(0xFF,printMessage);
    uds_wait();

/** Attention this function have only for debug purpose!
 *  DTC, prepared functions calls for debugging.

    UDS_DTC_ReportNumberOfDTCByStatusMask(0xFF,printMessage);
    uds_wait();

    UDS_DTC_ClearDiagnosticInformation(0xFFFFFF,printMessage);
    uds_wait();

    UDS_DTC_ReportNumberOfDTCByStatusMask(0xFF,printMessage);
    uds_wait();


    UDS_DTC_ReportNumberOfDTCByStatusMask(0xFF,printMessage);
    uds_wait();
    UDS_DTC_ReportDTCByStatusMask(0xFF,printMessage);
    uds_wait();
    UDS_DTC_ReportDTCSnapshotIdentification(printMessage);
    uds_wait();
    UDS_DTC_ReportDTCSnapshotRecordByDTCNumber(0x070809,2,printMessage);
    uds_wait();
    UDS_DTC_ReportDTCStoredDataByRecordNumber(0x01,printMessage);
    uds_wait();
    UDS_DTC_ReportDTCExtDataRecordByDTCNumber(0x010203, 0x02, printMessage);
    uds_wait();
    UDS_DTC_ReportNumberOfDTCBySeverityMaskRecord(0xFF, 0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportDTCBySeverityMaskRecord(0xFF, 0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportSeverityInformationOfDTC(0x070809, printMessage);
    uds_wait();
    UDS_DTC_ReportSupportedDTC(printMessage);
    uds_wait();
    UDS_DTC_ReportFirstTestFailedDTC(printMessage);
    uds_wait();
    UDS_DTC_ReportFirstConfirmedDTC(printMessage);
    uds_wait();
    UDS_DTC_ReportMostRecentTestFailedDTC(printMessage);
    uds_wait();
    UDS_DTC_ReportMostRecentConfirmedDTC(printMessage);
    uds_wait();
    UDS_DTC_ReportMirrorMemoryDTCByStatusMask(0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportMirrorMemoryDTCExtDataRecordByDTCNumber(0x070809, 0x03, printMessage);
    uds_wait();
    UDS_DTC_ReportNumberOfMirrorMemoryDTCByStatusMask(0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportNumberOfEmissionsOBDDTCByStatusMask(0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportEmissionsOBDDTCByStatusMask(0xFF, printMessage);
    uds_wait();
    UDS_DTC_ReportDTCFaultDetectionCounter(printMessage);
    uds_wait();
    UDS_DTC_ReportDTCExtDataRecordByRecordNumber(0x03,printMessage);
    uds_wait();
    UDS_DTC_ReportUserDefMemoryDTCByStatusMask(0xFF,1,printMessage);
    uds_wait();
    UDS_DTC_ReportUserDefMemoryDTCSnapshotRecordByDTCNumber(0x010203,0x02,1,printMessage);
    uds_wait();
    UDS_DTC_ReportUserDefMemoryDTCExtDataRecordByDTCNumber(0x040506,2,1,printMessage);
    uds_wait();
    UDS_DTC_ReportWWHOBDDTCByMaskRecord(1,1,1,printMessage);
    uds_wait();
    UDS_DTC_ReportWWHOBDDTCWithPermanentStatus(1,printMessage);
    uds_wait();
*/
}

/** @brief This Function calls alls implemented and integrated Input and Output Controller functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void IOControl() 
{

}

/** @brief This Function calls alls implemented and integrated Upload and Download functional Unit functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void UploadDownload() 
{

}

/** @brief This Function calls alls implemented and integrated Routine control functional Unit functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void Routine() 
{

}

/** @brief This Function calls alls implemented and integrated Service and Session Control Module functions.
 *         Used as showcase that communication between client and server is working.
 *         Function can be used to test client and server functionality.
 */
void DataTransmit() 
{

}




/* Private Function **********************************************************/

static void printMessage(UDS_Client_Error_t error, uint8_t* receive, uint32_t receive_length) 
{
    if(error != E_OK) 
    {
        UDS_LOG_WARNING("Got Error response %s (0x%02x)", ErrorCode_getString(error), error);
    }
    if(receive != NULL) 
    {
        printf("[UDS Client] CALLBACK: 0x");
        for (int i = 0; i < receive_length; i++) 
        {
            printf("%02x", receive[i]);
        }
        printf("\n"); 
    }
    return;
}

static void uds_wait()
{
    int counter = 0;
    while(E_Pending == UDS_Client_Task()) 
    {
        if(counter == 100) 
        {
            UDS_LOG_ERROR("Timeout.");
            break;
        }
        Sleep(100);
        counter++;
    }
    return;
}


/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
