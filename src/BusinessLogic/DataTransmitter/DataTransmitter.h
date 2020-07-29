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

#include "DataModels/MemoryDefinition.h"
#include "DataModels/DataDefinition.h"
#include "DataModels/TimerRates.h"
#include "Interfaces/CallbackInterface.h"
#include <stdint.h>
#include <stdbool.h>

bool readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, UDS_callback callback);
bool readMemoryByAddress(MemoryDefinition sourceMemory, UDS_callback callback);
/**
 * Very Complex. Might need the user to interpret the return values
 */
bool readScalingDataByIdentifier(uint16_t dataIdentifier, UDS_callback callback);
bool ReadDataByPeriodicIdentifier(TimerRates_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength, UDS_callback callback, UDS_callback response_callback);
bool stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength, UDS_callback callback);
/**
 * If Both Lengths are 0, the Identifier will be cleared.
 */
bool dynamicallyDefineDataIdentifier(uint16_t definedDataIdentifier, DataDefinition* SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, MemoryDefinition* SourceMemoryDefinitions, uint8_t SourceMemoryLength, UDS_callback callback);
bool writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback);
bool writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory, UDS_callback callback);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_B5D43F1B_EA2F_4dd9_ADDA_89D31FE79F42__INCLUDED_)*/
 