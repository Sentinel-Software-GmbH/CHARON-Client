/**
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
/*****************************************************************************/

/* Includes ******************************************************************/

#include "unity.h"
#include "UploadDownload.h"
#include "mock_SessionAndTransportManager.h"


/* Imports *******************************************************************/

/* Constants *****************************************************************/
const uint8_t address[] = { 0x00, 0x01, 0x00, 0x00 };
const uint8_t memory[] = { 0x00 , 0x00, 0x00, 0x10 };
const MemoryDefinition mem = {address, memory, 4, 4};
const uint8_t data[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

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
    uint8_t* expectedData = (uint8_t[]) {SID_RequestDownload, 0x00, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };
    STM_Deploy_ExpectAndReturn(expectedData, 11, NULL, false, true);
    UDS_UPDOWN_DownloadRequest(0x00, 0x00, mem);
    expectedData = (uint8_t[]) {SID_TransferData, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    STM_Deploy_ExpectWithArrayAndReturn(expectedData, 18, 18, NULL, false, true);
    UDS_UPDOWN_Download(0x00, data, 16);
    UDS_UPDOWN_RequestTransferExit(NULL, 0);
}



void test_UploadDataFromMemory() {
    uint8_t rxBuffer[16];
    uint8_t* expectedData = (uint8_t[]) {SID_RequestUpload, 0x00, 0x44, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10 };
    STM_Deploy_ExpectAndReturn(expectedData, 11, NULL, false, true);
    UDS_UPDOWN_UploadRequest(0x00, 0x00, mem);
    expectedData = (uint8_t[]) {SID_TransferData, 0x00};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    UDS_UPDOWN_Upload(0x00, 16);
    UDS_UPDOWN_RequestTransferExit(NULL, 0);
}

void test_FileHandling() {
    
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/