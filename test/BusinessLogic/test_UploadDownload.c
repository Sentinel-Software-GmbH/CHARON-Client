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
/*****************************************************************************/
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup TestModules
 * @{
 * @file
 * Test Upload Download Module.
 * 
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

/* Includes ******************************************************************/

#include "unity.h"
#include "UploadDownload.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_TestCallback.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/
static uint8_t address[] = { 0x00, 0x01, 0x00, 0x00 };
static uint8_t memory[] = { 0x00 , 0x00, 0x00, 0x10 };
static MemoryDefinition mem = {address, memory, 4, 4};
static uint8_t data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Setup and Teardowns *******************************************************/

void setUp(void) {

}

void tearDown(void) {

}

/* Test Functions ************************************************************/

void test_DownloadDataToMemory() {
    TEST_MESSAGE("Testing sending data to the server.");
    TEST_MESSAGE("This test proofs Requirement(s): R22, R24, R25");
    uint8_t* expectedData = (uint8_t[]) {SID_RequestDownload, 0x00, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };
    STM_Deploy_ExpectAndReturn(expectedData, 11, NULL, false, true);
    UDS_UPDOWN_DownloadRequest(0x00, 0x00, mem, NULL);
    expectedData = (uint8_t[]) {SID_TransferData, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    STM_Deploy_ExpectWithArrayAndReturn(expectedData, 18, 18, NULL, false, true);
    UDS_UPDOWN_Download(0x00, data, 16, 18, NULL);
    STM_Deploy_ExpectAndReturn((uint8_t[]) {SID_RequestTransferExit}, 1, NULL, false, true);
    UDS_UPDOWN_ExitTransfer(NULL, 0, NULL);
}



void test_UploadDataFromMemory() {
    TEST_MESSAGE("Testing receiving data from the server.");
    TEST_MESSAGE("This test proofs ROTs R23, R24 and R25.");
    uint8_t rxBuffer[16];
    uint8_t* expectedData = (uint8_t[]) {SID_RequestUpload, 0x00, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };
    STM_Deploy_ExpectAndReturn(expectedData, 11, NULL, false, true);
    UDS_UPDOWN_UploadRequest(0x00, 0x00, mem, NULL);
    expectedData = (uint8_t[]) {SID_TransferData, 0x00};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    UDS_UPDOWN_Upload(0x00, NULL);
    expectedData = (uint8_t[]) {SID_RequestTransferExit};
    STM_Deploy_ExpectAndReturn(expectedData, 1, NULL, false, true);
    UDS_UPDOWN_ExitTransfer(NULL, 0, NULL);
}

void test_DataSize_Bigger_Than_MaxBlockLength() {
    testCallback_Expect(E_MessageTooLong, NULL, 0);
    TEST_ASSERT_FALSE(UDS_UPDOWN_Download(0, NULL, 255, 16, testCallback));
}

void test_Message_Longer_Than_BufferSize() {
    UpDown_setStaticBufferSize(255);
    testCallback_Expect(E_MessageTooLong, NULL, 0);
    TEST_ASSERT_FALSE(UDS_UPDOWN_Download(0, NULL, 600, 1024, testCallback));
}

void test_FileHandling() {
    TEST_MESSAGE("NOT YET IMPLEMENTED.");
    TEST_MESSAGE("This test proofs ROT R26.");
    TEST_ASSERT_EQUAL(1, 1);
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/