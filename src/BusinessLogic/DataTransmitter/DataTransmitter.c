/****************************************************
 *  DataTransmitter.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DataTransmitter       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "DataTransmitter.h"
#include "DataModels/SID.h"
#include "ComLogic/SessionAndTransportManager.h"
#include <stdint.h>
#include <string.h>

#define MAX(x, y) (x > y ? x : y)

bool readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, UDS_callback callback)
{
	uint8_t message[1 + length * 2];
	message[0] = SID_ReadDataByIdentifier;
	for(int i = 0; i < length; i++) {
		message[i*2+1] = (dataIdentifier[i] >> 8) & 0xFF;
		message[i*2+2] = (dataIdentifier[i]) & 0xFF;
	}
	return STM_Deploy(message, 1 + length * 2, callback, false);
}

bool readMemoryByAddress(MemoryDefinition sourceMemory, UDS_callback callback)
{
	uint32_t length = 2 + sourceMemory.AddressLength + sourceMemory.SizeLength;
	uint8_t message[length];
	message[0] = SID_ReadMemoryByAdress;
	message[1] = MemoryDefinition_getAddressAndLengthFormatIdentifier(&sourceMemory);
	memcpy(&message[2], sourceMemory.Address, sourceMemory.AddressLength);
	memcpy(&message[2+sourceMemory.AddressLength], sourceMemory.Size, sourceMemory.SizeLength);
	return STM_Deploy(message, length, callback, false);
}

/**
 * Very Complex. Might need the user to interpret the return values
 */
bool readScalingDataByIdentifier(uint16_t dataIdentifier, UDS_callback callback)
{
	uint8_t message[] = {SID_ReadScalingDataByIdentifier, (dataIdentifier >> 8) & 0xFF, dataIdentifier & 0xFF};
	return STM_Deploy(message, 3, callback, false);
}

bool ReadDataByPeriodicIdentifier(TimerRates_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength, UDS_callback callback, UDS_callback response_callback)
{
	uint8_t message[2+periodicDataIdLength];
	message[0] = SID_ReadDataByPeriodicIdentifier;
	message[1] = transmissionMode;
	memcpy(&message[2], periodicDataIdentifiers, periodicDataIdLength);
	bool retVal = STM_Deploy(message, 2+periodicDataIdLength, callback, false);
	retVal &= STM_AsyncDeploy(SID_ReadDataByPeriodicIdentifier, response_callback);
	return retVal;
}

bool stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength, UDS_callback callback)
{
	uint8_t message[2+periodicDataIdsLength];
	message[0] = SID_ReadDataByPeriodicIdentifier;
	message[1] = 0x04;
	memcpy(&message[2], periodicDataIdentifiers, periodicDataIdsLength);
	return STM_Deploy(message, 2+periodicDataIdsLength, callback, false);
}

/**
 * If Both Lengths are 0, the Identifier will be cleared.
 */
bool dynamicallyDefineDataIdentifier(uint16_t definedDataIdentifier, DataDefinition* SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, MemoryDefinition* SourceMemoryDefinitions, uint8_t SourceMemoryLength, UDS_callback callback)
{
	uint32_t didLength = SourceDataDefinitionsLength * sizeof(DataDefinition);
	uint32_t memoryLength = SourceMemoryLength * sizeof(MemoryDefinition);
	uint32_t length = MAX(didLength, memoryLength);
	uint8_t message[length];
	return false;
}

bool writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback)
{
	return false;
}

bool writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory, UDS_callback callback)
{
	return false;
} 

