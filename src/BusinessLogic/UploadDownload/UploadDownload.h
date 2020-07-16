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

void Download(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, uint8_t* data);
void Upload(uint8_t compressionMethod, uint8_t encryptionMethod, MemoryDefinition memoryDefinition, uint8_t dataBuffer);
void AddFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptingMethod, uint8_t fileSizeParameterLength, uint8_t* fileSizeUncompressed, uint8_t* fileSizeCompressed, uint8_t* data, boolean replace);
void DeleteFile(uint16_t pathLength, char* path);
void ReadFile(uint16_t pathLength, char* path, uint8_t compressionMethod, uint8_t encryptionMethod, uint8_t* buffer, uint8_t* returnedFileSize);
void ReadDir(uint16_t pathLength, char* path, uint8_t* buffer, uint8_t* dirSize);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_ACF1E883_4B6F_43d1_93A7_FE33562A95D4__INCLUDED_)*/
 