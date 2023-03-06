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
 * Implementation of the Stored Data Transmitter Functional Unit.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 *****************************************************************************/

/* Includes ******************************************************************/

#include "StoredDataTransmitter.h"
#include "SID.h"
#include "SessionAndTransportManager.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Private Function Definitions **********************************************/

/* Interfaces  ***************************************************************/

bool UDS_DTC_ClearDiagnosticInformation(uint32_t groupOfDTC, UDS_callback callback)
{
	uint8_t message[4];
    message[0] = SID_ClearDiagnosticInformation;
    message[1] = groupOfDTC >> 16;
    message[2] = groupOfDTC >> 8;
    message[3] = groupOfDTC;
    return STM_Deploy(message, 4, callback, false);
}

/* 0x01 */
bool UDS_DTC_ReportNumberOfDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x01;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x02 */
bool UDS_DTC_ReportDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x02;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x03 */
bool UDS_DTC_ReportDTCSnapshotIdentification(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x03;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x04 */
bool UDS_DTC_ReportDTCSnapshotRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCSnapshotRecordNumber, UDS_callback callback)
{
    uint8_t message[6];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x04;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    message[5] = DTCSnapshotRecordNumber;
    return STM_Deploy(message, 6, callback, false);
}

/* 0x05 */
bool UDS_DTC_ReportDTCStoredDataByRecordNumber(uint8_t DTCStoredDataRecordNumber, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x05;
    message[2] = DTCStoredDataRecordNumber;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x06 */
bool UDS_DTC_ReportDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, UDS_callback callback)
{
    uint8_t message[6];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x06;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    message[5] = DTCExtDataRecordNumber;
    return STM_Deploy(message, 6, callback, false);
}

/* 0x07 */
bool UDS_DTC_ReportNumberOfDTCBySeverityMaskRecord(uint8_t DTCSeverityMask, uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[4];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x07;
    message[2] = DTCSeverityMask;
    message[3] = DTCStatusMask;
    return STM_Deploy(message, 4, callback, false);
}

/* 0x08 */
bool UDS_DTC_ReportDTCBySeverityMaskRecord(uint8_t DTCSeverityMask, uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[4];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x08;
    message[2] = DTCSeverityMask;
    message[3] = DTCStatusMask;
    return STM_Deploy(message, 4, callback, false);
}

/* 0x09 */
bool UDS_DTC_ReportSeverityInformationOfDTC(uint32_t DTCMaskRecord, UDS_callback callback)
{
    uint8_t message[5];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x09;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    return STM_Deploy(message, 5, callback, false);
}

/* 0x0A */
bool UDS_DTC_ReportSupportedDTC(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0A;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x0B */
bool UDS_DTC_ReportFirstTestFailedDTC(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0B;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x0C */
bool UDS_DTC_ReportFirstConfirmedDTC(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0C;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x0D */
bool UDS_DTC_ReportMostRecentTestFailedDTC(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0D;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x0E */
bool UDS_DTC_ReportMostRecentConfirmedDTC(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0E;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x0F */
bool UDS_DTC_ReportMirrorMemoryDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x0F;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x10 */
bool UDS_DTC_ReportMirrorMemoryDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, UDS_callback callback)
{
    uint8_t message[6];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x10;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    message[5] = DTCExtDataRecordNumber;
    return STM_Deploy(message, 6, callback, false);
}

/* 0x11 */
bool UDS_DTC_ReportNumberOfMirrorMemoryDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x11;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x12 */
bool UDS_DTC_ReportNumberOfEmissionsOBDDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x12;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x13 */
bool UDS_DTC_ReportEmissionsOBDDTCByStatusMask(uint8_t DTCStatusMask, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x13;
    message[2] = DTCStatusMask;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x14 */
bool UDS_DTC_ReportDTCFaultDetectionCounter(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x14;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x15 */
bool UDS_DTC_ReportDTCWithPermanentStatus(UDS_callback callback)
{
    uint8_t message[2];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x15;
    return STM_Deploy(message, 2, callback, false);
}

/* 0x16 */
bool UDS_DTC_ReportDTCExtDataRecordByRecordNumber(uint8_t DTCExtDataRecordNumber, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x16;
    if (DTCExtDataRecordNumber > 0xEF) DTCExtDataRecordNumber = 0xEF;
    message[2] = DTCExtDataRecordNumber;
    return STM_Deploy(message, 3, callback, false);
}

/* 0x17 */
bool UDS_DTC_ReportUserDefMemoryDTCByStatusMask(uint8_t DTCStatusMask, uint8_t MemorySelection, UDS_callback callback)
{
    uint8_t message[4];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x17;
    message[2] = DTCStatusMask;
    message[3] = MemorySelection;
    return STM_Deploy(message, 4, callback, false);
}

/* 0x18 */
bool UDS_DTC_ReportUserDefMemoryDTCSnapshotRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCSnapshotRecordNumber, uint8_t MemorySelection, UDS_callback callback)
{
    uint8_t message[7];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x18;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    message[5] = DTCSnapshotRecordNumber;
    message[6] = MemorySelection;
    return STM_Deploy(message, 7, callback, false);
}

/* 0x19 */
bool UDS_DTC_ReportUserDefMemoryDTCExtDataRecordByDTCNumber(uint32_t DTCMaskRecord, uint8_t DTCExtDataRecordNumber, uint8_t MemorySelection, UDS_callback callback)
{    
    uint8_t message[7];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x19;
    message[2] = DTCMaskRecord >> 16;
    message[3] = DTCMaskRecord >> 8;
    message[4] = DTCMaskRecord;
    message[5] = DTCExtDataRecordNumber;
    message[6] = MemorySelection;
    return STM_Deploy(message, 7, callback, false);

}

/* 0x42 */
bool UDS_DTC_ReportWWHOBDDTCByMaskRecord(uint8_t FunctionalGroupIdentifier, uint8_t DTCStatusMask, uint8_t DTCSeverityMask, UDS_callback callback)
{
    uint8_t message[5];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x42;
    message[2] = FunctionalGroupIdentifier;
    message[3] = DTCStatusMask;
    message[4] = DTCSeverityMask;
    return STM_Deploy(message, 5, callback, false);
}

/* 0x55 */
bool UDS_DTC_ReportWWHOBDDTCWithPermanentStatus(uint8_t FunctionalGroupIdentifier, UDS_callback callback)
{
    uint8_t message[3];
    message[0] = SID_ReadDTCInformation;
    message[1] = 0x55;
    message[2] = FunctionalGroupIdentifier;
    return STM_Deploy(message, 3, callback, false);
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
