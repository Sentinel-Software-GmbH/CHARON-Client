/**
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
/*****************************************************************************/

/* Includes ******************************************************************/

#include "unity.h"
#include "StoredDataTransmitter.h"
#include "DataModels/SID.h"
#include "mock_SessionAndTransportManager.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Setup and Teardowns *******************************************************/

void setUp(void) {

}

void tearDown(void) {

}

/* Test Functions ************************************************************/

void test_ClearDTC(void) {
    TEST_MESSAGE("Testing the clearing of diagnostic information.");
    uint8_t *expectedData = (uint8_t[]) {SID_ClearDiagnosticInformation, 0x22, 0x33, 0x44};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ClearDiagnosticInformation(0x11223344, NULL));
    TEST_PASS_MESSAGE("This proves R18");
}

void test_ReportNumberOfDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x01, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportNumberOfDTCByStatusMask(0xFF, NULL));
}

void test_reportDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x02, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCByStatusMask(0xFF, NULL));
}

void test_reportDTCSnapshotIdentification(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x03};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCSnapshotIdentification(NULL));
}

void test_reportDTCSnapshotRecordByDTCNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x04, 0x22, 0x33, 0x44, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCSnapshotRecordByDTCNumber(0x11223344, 0xFF, NULL));
}

void test_reportDTCStoredDataByRecordNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x05, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCStoredDataByRecordNumber(0xFF, NULL));
}

void test_reportDTCExtDataRecordByDTCNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x06, 0x22, 0x33, 0x44, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCExtDataRecordByDTCNumber(0x11223344, 0xFF, NULL));
}

void test_reportNumberOfDTCBySeverityMaskRecord(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x07, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportNumberOfDTCBySeverityMaskRecord(0xFF, 0xFF, NULL));
}

void test_reportDTCBySeverityMaskRecord(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x08, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCBySeverityMaskRecord(0xFF, 0xFF, NULL));
}

void test_reportSeverityInformationOfDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x09, 0x22, 0x33, 0x44};
    STM_Deploy_ExpectAndReturn(expectedData, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportSeverityInformationOfDTC(0x11223344, NULL));
}

void test_reportSupportedDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0A};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportSupportedDTC(NULL));
}

void test_reportFirstTestFailedDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0B};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportFirstTestFailedDTC(NULL));
}

void test_reportFirstConfirmedDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0C};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportFirstConfirmedDTC(NULL));
}

void test_reportMostRecentTestFailedDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0D};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportMostRecentTestFailedDTC(NULL));
}

void test_reportMostRecentConfirmedDTC(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0E};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportMostRecentConfirmedDTC(NULL));
}

void test_reportMirrorMemoryDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x0F, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportMirrorMemoryDTCByStatusMask(0xFF, NULL));
}

void test_reportMirrorMemoryDTCExtDataRecordByDTCNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x10, 0x22, 0x33, 0x44, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportMirrorMemoryDTCExtDataRecordByDTCNumber(0x11223344, 0xFF, NULL));
}

void test_reportNumberOfMirrorMemoryDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x11, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportNumberOfMirrorMemoryDTCByStatusMask(0xFF, NULL));
}

void test_reportNumberOfEmissionsOBDDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x12, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportNumberOfEmissionsOBDDTCByStatusMask(0xFF, NULL));
}

void test_reportEmissionsOBDDTCByStatusMask(void) {
    uint8_t* expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x13, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportEmissionsOBDDTCByStatusMask(0xFF, NULL));
}

void test_reportDTCFaultDetectionCounter(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x14};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCFaultDetectionCounter(NULL));
}

void test_reportDTCWithPermanentStatus(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x15};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCWithPermanentStatus(NULL));
}

void test_reportDTCExtDataRecordByRecordNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x16, 0xEF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportDTCExtDataRecordByRecordNumber(0xFF, NULL));
}

void test_reportUserDefMemoryDTCByStatusMask(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x17, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportUserDefMemoryDTCByStatusMask(0xFF, 0xFF, NULL));
}

void test_reportUserDefMemoryDTCSnapshotRecordByDTCNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x18, 0x22, 0x33, 0x44, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 7, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportUserDefMemoryDTCSnapshotRecordByDTCNumber(0x11223344, 0xFF, 0xFF, NULL));
}

void test_reportUserDefMemoryDTCExtDataRecordByDTCNumber(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x19, 0x22, 0x33, 0x44, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 7, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportUserDefMemoryDTCExtDataRecordByDTCNumber(0x11223344, 0xFF, 0xFF, NULL));
}

void test_reportWWHOBDDTCByMaskRecord(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x42, 0xFF, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportWWHOBDDTCByMaskRecord(0xFF, 0xFF, 0xFF, NULL));
}

void test_reportWWHOBDDTCWithPermanentStatus(void) {
    uint8_t *expectedData = (uint8_t[]) {SID_ReadDTCInformation, 0x55, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DTC_ReportWWHOBDDTCWithPermanentStatus(0xFF, NULL));
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/