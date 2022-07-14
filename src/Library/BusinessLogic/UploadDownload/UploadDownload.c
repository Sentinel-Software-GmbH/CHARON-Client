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
 * @file UploadDownload.c
 * Implementation of the Service and Session Control Module
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

/* Includes ******************************************************************/

#include <string.h>
#include "UploadDownload.h"
#include "config.h"
#include "CallbackInterface.h"
#include "SID.h"
#include "SessionAndTransportManager.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

#ifdef TEST
    static uint32_t STATIC_BUFFER_SIZE = UPLOAD_DOWNLOAD_STATIC_BUFFER_SIZE;
#else
    #define STATIC_BUFFER_SIZE UPLOAD_DOWNLOAD_STATIC_BUFFER_SIZE
#endif
#if UPLOAD_DOWNLOAD_USES_STATIC_BUFFER == 1
    static uint8_t txBuffer[UPLOAD_DOWNLOAD_STATIC_BUFFER_SIZE];
#endif

/* Private Function Definitions **********************************************/

bool request(bool upload, uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback);

/* Interfaces  ***************************************************************/

bool UDS_UPDOWN_DownloadRequest(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback) {
    return request(false, compressionMethod, encryptionMethod, memoryDefinition, callback);
}

bool UDS_UPDOWN_Download(uint8_t blockSequenceCounter, uint8_t* data, uint32_t dataSize, uint32_t maxNumberOfBlockLength, UDS_callback callback) {
    uint32_t length = maxNumberOfBlockLength;
#if UPLOAD_DOWNLOAD_USES_STATIC_BUFFER == 0
    uint8_t txBuffer[length];
#else
    if (length > STATIC_BUFFER_SIZE) { 
        if(callback != NULL) {
            callback(E_MessageTooLong, NULL, 0);
        }
        return false;
    }
#endif
    if(dataSize > maxNumberOfBlockLength - 2) {
        if (callback != NULL) {
            callback(E_MessageTooLong, NULL, 0);
        }
        return false;
    }
    UDS_MUTEX_LOCK();
    txBuffer[0] = SID_TransferData;
    txBuffer[1] = blockSequenceCounter;
    memcpy(&txBuffer[2], data, dataSize);
    UDS_MUTEX_UNLOCK();
    return STM_Deploy(txBuffer, length, callback, false);
}

bool UDS_UPDOWN_UploadRequest(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback) {
    return request(true, compressionMethod, encryptionMethod, memoryDefinition, callback);
}

bool UDS_UPDOWN_Upload(uint8_t blockSequenceCounter, UDS_callback callback) {
    uint32_t length = 2;
#if UPLOAD_DOWNLOAD_USES_STATIC_BUFFER == 0
    uint8_t txBuffer[length];
#else
    if (length > STATIC_BUFFER_SIZE) {
        if(callback != NULL) {
            callback(E_MessageTooLong, NULL, 0);
        }
        return false;
    }
#endif
    UDS_MUTEX_LOCK();
    txBuffer[0] = SID_TransferData;
    txBuffer[1] = blockSequenceCounter;
    UDS_MUTEX_UNLOCK();
    STM_Deploy(txBuffer, 2, callback, false);
}

bool UDS_UPDOWN_ExitTransfer(uint8_t *vendorSpecificServiceParameter, uint32_t lengthOfParameter, UDS_callback callback) {
    uint32_t length = 1 + lengthOfParameter;
#if UPLOAD_DOWNLOAD_USES_STATIC_BUFFER == 0
    uint8_t txBuffer[length];
#else
    if (length > STATIC_BUFFER_SIZE) {
        if(callback != NULL) {
            callback(E_MessageTooLong, NULL, 0);
        }
        return false;
    }
#endif
    UDS_MUTEX_LOCK();
    txBuffer[0] = SID_RequestTransferExit;
    memcpy(&txBuffer[1], vendorSpecificServiceParameter, lengthOfParameter);
    UDS_MUTEX_UNLOCK();
    STM_Deploy(txBuffer, length, callback, false);
}

bool UDS_UPDOWN_AddFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptingMethod, uint8_t fileSizeParameterLength, uint8_t* fileSizeUncompressed, uint8_t* fileSizeCompressed, bool replace) {}
bool UDS_UPDOWN_DeleteFile(uint16_t pathLength, char* path) {}
bool UDS_UPDOWN_ReadFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptionMethod, UDS_callback callback);
bool UDS_UPDOWN_ReadDir(uint16_t pathLength, char* path, UDS_callback callback);

/* Private Function **********************************************************/

bool request(bool upload, uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback) {
    uint32_t length = 3 + memoryDefinition.AddressLength + memoryDefinition.SizeLength;
#if UPLOAD_DOWNLOAD_USES_STATIC_BUFFER == 0
    uint8_t txBuffer[length];
#else
    if (length > STATIC_BUFFER_SIZE) {
        if(callback != NULL) {
            callback(E_MessageTooLong, NULL, 0);
        }
        return false;
    }
#endif
    UDS_MUTEX_LOCK();
    txBuffer[0] = upload ? SID_RequestUpload : SID_RequestDownload;
    uint8_t dataFormatIdentifier = (compressionMethod << 4) | (encryptionMethod & 0xF);
    txBuffer[1] = dataFormatIdentifier;
    txBuffer[2] = memoryDefinition.SizeLength << 4 | (memoryDefinition.AddressLength & 0xF);
    memcpy(&txBuffer[3], memoryDefinition.Address, memoryDefinition.AddressLength);
    memcpy(&txBuffer[3 + memoryDefinition.AddressLength], memoryDefinition.Size, memoryDefinition.SizeLength);
    UDS_MUTEX_UNLOCK();
    return STM_Deploy(txBuffer, length, callback, false);
}

/* TEST INJECTION FUNCTIONS **************************************************/
#ifdef TEST
    void UpDown_setStaticBufferSize(uint32_t newSize) { STATIC_BUFFER_SIZE = newSize; }
#endif


/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/








/* Architektur Dokument, Test Dokument, Test Log, Source Documentation, Test Source Documentation, BA */
/* Was war gefordert. Wer ist Beteiligt, Welche Requirements */