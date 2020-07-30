/****************************************************
 *  UploadDownload.h                                         
 *  Created on: 16-Jul-2020 09:30:00                      
 *  Implementation of the Class UploadDownload       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_ACF1E883_4B6F_43d1_93A7_FE33562A95D4__INCLUDED_)
#define EA_ACF1E883_4B6F_43d1_93A7_FE33562A95D4__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <DataModels/MemoryDefinition.h>

void UDS_UPDOWN_Download(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, uint8_t* data);
void UDS_UPDOWN_Upload(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, uint8_t dataBuffer);
void UDS_UPDOWN_AddFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptingMethod, uint8_t fileSizeParameterLength, uint8_t* fileSizeUncompressed, uint8_t* fileSizeCompressed, uint8_t* data, bool replace);
void UDS_UPDOWN_DeleteFile(uint16_t pathLength, char* path);
void UDS_UPDOWN_ReadFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptionMethod, uint8_t* buffer, uint8_t* returnedFileSize);
void UDS_UPDOWN_ReadDir(uint16_t pathLength, char* path, uint8_t* buffer, uint8_t* dirSize);

#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_ACF1E883_4B6F_43d1_93A7_FE33562A95D4__INCLUDED_)*/
 