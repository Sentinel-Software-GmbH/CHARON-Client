/****************************************************
 *  DataTransmitter.h                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DataTransmitter       
 *  Original author: Steven Inacio                     
 ****************************************************/

#if !defined(EA_B5D43F1B_EA2F_4dd9_ADDA_89D31FE79F42__INCLUDED_)
#define EA_B5D43F1B_EA2F_4dd9_ADDA_89D31FE79F42__INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif

#include "MemoryDefinition.h"

uint8_t readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, uint8_t buffer);
uint8_t readMemoryByAddress(MemoryDefinition sourceMemory, uint8_t buffer);
/**
 * Very Complex. Might need the user to interpret the return values
 */
uint8_t readScalingDataByIdentifier(uint16_t dataIdentifier, uint8_t buffer);
uint8_t controlReadDataByPeriodicIdentifier(uint8_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength);
void readDataByPeriodicIdentifier(uint8_t buffer);
void stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength);
/**
 * If Both Lengths are 0, the Identifier will be cleared.
 */
void dynamicallyDefineDataIdentifier(uin16_t definedDataIdentifier, DataDefinition* SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, MemoryDefinition* SourceMemoryDefinitions, uint8_t SourceMemoryLength);
void writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength);
void writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_B5D43F1B_EA2F_4dd9_ADDA_89D31FE79F42__INCLUDED_)*/
 