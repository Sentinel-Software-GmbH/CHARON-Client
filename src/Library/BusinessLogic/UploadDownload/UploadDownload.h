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
 * 
 *  Created on: 16.07.2018
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup ComLogic
 * @{
 * @file UploadDownload.h
 * Provides functions to transmit data to and from the server.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/


#ifndef UDS_UPLOAD_DOWNLOAD_H_
#define UDS_UPLOAD_DOWNLOAD_H_

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ******************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "Interfaces/CallbackInterface.h"
#include "DataModels/MemoryDefinition.h"

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Interfaces ****************************************************************/

/** Sends a Request to Transfer Data from the client to the server.
 * This puts the server into Data Transmission mode.
 * @note After a positive Response the User needs to call UDS_UPDOWN_Download() as many times as needed with the maxNumberOfBlockLength that was in the response message of the server.
 * After the Transfer has finished a UDS_UPDOWN_ExitTransfer() request needs to be sent to the server to release it from the Data Transmission Mode. 
 * 
 * @param compressionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param encryptionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param memoryDefinition A Data structure representing a pointer and the size of some data in the memory of the server.
 * @param callback A User provided callback that get executed when the Service has finished.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_DownloadRequest(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback);

/** Send data to the server.
 * @param blockSequenceCounter Similiar to the TCP Sequence Number. If the block was successfully transmitted this number will increase by 1, else it indicates that the last block needs to be send again. It wraps around 0xFF to 0x00.
 * @param data Pointer to the data that needs to be sent to the server.
 * @param dataSize Size of the data. <br>@b WARNING: dataSize must always be less than or equal to (maxNumberOfBlockLength - 2).
 * @param maxNumberOfBlockLength The maximum allowed message length. <br>@b WARNING: This does also include the service identifier and the service parameters. <br>@b NOTE: This value is found in the positive Response from the UDS_UPDOWN_DownloadRequest().
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_Download(uint8_t blockSequenceCounter, uint8_t* data, uint32_t dataSize, uint32_t maxNumberOfBlockLength, UDS_callback callback);

/** Sends a Request to Transfer Data from the server to the client.
 * This puts the server into Data Transmission mode.
 * @note After a positive Response the user needs to call UDS_UPDOWN_Upload() as many times as needed with the maxNumberOfBlockLength that was in the positive response message of the server.
 * After the Transfer has finished a UDS_UPDOWN_ExitTransfer() request need to be sent ot the server to releaseit from the Data Transmission Mode.
 * 
 * @param compressionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param encryptionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param memoryDefinition A Data structure representing a pointer and the size of some data in the memory of the server.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_UploadRequest(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, UDS_callback callback);

/** Receives data from the server.
 * @param blockSequenceCounter Similiar to the TCP Sequence Number. If the block was successfully transmitted this number will increase by 1, else it indicates that the last block needs to be send again. It wraps around 0xFF to 0x00.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_Upload(uint8_t blockSequenceCounter, UDS_callback callback);

/** Releases the Server from Data Transmission Mode.
 * @param vendorSpecificServiceParameter Vendor specific parameters to support the transfer of data.
 * @param lengthOfParameter Size of the vendorSpecificServiceParameter data.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_ExitTransfer(uint8_t *vendorSpecificServiceParameter, uint32_t lengthOfParameter, UDS_callback callback);

/** Sends a Request to add a file on the server's file system.
 * This puts the server into Data Transmission Mode.
 * @note After this you need to send the file contents with UDS_UPDOWN_Download() and conclude the Transfer with UDS_UPDOWN_ExitTransfer()
 * @param pathLength Number of characters inside the pathLength.
 * @param path Destination Path on the server's file system. <br>@b NOTE: This includes the filename.
 * @param compressionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param encryptionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param fileSizeParameterLength Defines the length in bytes for both parameters fileSizeUncompressed and fileSizeCompressed.
 * @param fileSizeUncompressed The Size of the file after decompression. <br>@b NOTE: This needs to be present even if no compression method has been used.
 * @param fileSizeCompressed The size of the file after compression. <br>@b NOTE: this needs to be present even if no compression method has been used.
 * @param replace If this is true, the server will overwrite any existing file with the following data. <br>@b NOTE: How the server behaves when a file already exists but no overwrite was requested was not clearly described in the ISO spec, the Author believes a negative Response Message with the Value 0x70 (UploadDownloadNotAccepted) will be sent by the server.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_AddFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptingMethod, uint8_t fileSizeParameterLength, uint8_t* fileSizeUncompressed, uint8_t* fileSizeCompressed, bool replace);

/** Deletes a file from the server's filesystem.
 * This does NOT put the server into data transmission mode.
 * @param pathLength Number of characters inside the path.
 * @param path Destination Path on the server's file system. <br>@b NOTE: This includes the filename.
 */
bool UDS_UPDOWN_DeleteFile(uint16_t pathLength, char* path);

/** Reads out content from a file on the server's filesystem.
 * This puts the server into data transmission mode.
 * @param pathLength Number of characters inside the path.
 * @param path Destination Path on the server's file system. <br>@b NOTE: This includes the filename.
 * @param compressionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param encryptionMethod Anything other than 0x0 is vendor-specific. Check ISO 14229-1 Chapter 14.2 Table 394 under dataFormatIdentifier.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_ReadFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptionMethod, UDS_callback callback);

/**
 * Reads out the contents of a complete folder on the server's filesystem.
 * @param pathLength Number of characters inside the path.
 * @param path Destination Path on the server's file system. <br>@b NOTE: This includes the filename.
 * @param callback A user provided callback function that gets executed when a Server response was received or an error has occured.
 * @returns An Indicator for the successful deployment of the message.
 * This does not mean that the Service was also successful, just that the client has transmitted the request to the server.
 */
bool UDS_UPDOWN_ReadDir(uint16_t pathLength, char* path, UDS_callback callback);

#ifndef DOXY_SKIP
/* TEST INJECTION FUNCTIONS **************************************************/
#ifdef TEST
    void UpDown_setStaticBufferSize(uint32_t newSize);
#endif
#endif

#ifdef __cplusplus
}
#endif


#endif /* UDS_UPLOAD_DOWNLOAD_H_ */
 
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/






