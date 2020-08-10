/****************************************************
 *  DataTransmitter.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DataTransmitter       
 *  Original author: Steven Inacio                     
 ****************************************************/

/* Includes */

#include "DataTransmitter.h"
#include "ComLogic/SessionAndTransportManager.h"
#include "DataModels/SID.h"
#include <stdint.h>
#include <string.h>

/* Types */

/* Constants */

/* Variables */

/* Private Function Definitions */

#define MAX(x, y) (x > y ? x : y)

/* Interfaces */

bool UDS_DT_readDataByIdentifier(uint16_t *dataIdentifier, uint8_t length, UDS_callback callback)
{
	uint8_t message[1 + length * 2];
	message[0] = SID_ReadDataByIdentifier;
	for (uint16_t i = 0; i < length; i++)
	{
		message[i * 2 + 1] = (dataIdentifier[i] >> 8) & 0xFF;
		message[i * 2 + 2] = (dataIdentifier[i]) & 0xFF;
	}
	return STM_Deploy(message, 1 + length * 2, callback, false);
}

bool UDS_DT_readMemoryByAddress(MemoryDefinition sourceMemory, UDS_callback callback)
{
	uint32_t length = 2 + sourceMemory.AddressLength + sourceMemory.SizeLength;
	uint8_t message[length];
	message[0] = SID_ReadMemoryByAdress;
	message[1] = MemoryDefinition_getAddressAndLengthFormatIdentifier(&sourceMemory);
	memcpy(&message[2], sourceMemory.Address, sourceMemory.AddressLength);
	memcpy(&message[2 + sourceMemory.AddressLength], sourceMemory.Size, sourceMemory.SizeLength);
	return STM_Deploy(message, length, callback, false);
}

/**
 * Very Complex. Might need the user to interpret the return values
 */
bool UDS_DT_readScalingDataByIdentifier(uint16_t dataIdentifier, UDS_callback callback)
{
	uint8_t message[] = {SID_ReadScalingDataByIdentifier, (dataIdentifier >> 8) & 0xFF, dataIdentifier & 0xFF};
	return STM_Deploy(message, 3, callback, false);
}

bool UDS_DT_ReadDataByPeriodicIdentifier(TimerRates_t transmissionMode, uint8_t *periodicDataIdentifiers, uint8_t periodicDataIdLength, UDS_callback callback, UDS_callback response_callback)
{
	uint8_t message[2 + periodicDataIdLength];
	message[0] = SID_ReadDataByPeriodicIdentifier;
	message[1] = transmissionMode;
	memcpy(&message[2], periodicDataIdentifiers, periodicDataIdLength);
	bool retVal = STM_Deploy(message, 2 + periodicDataIdLength, callback, false);
	retVal &= STM_AsyncDeploy(SID_ReadDataByPeriodicIdentifier, response_callback);
	return retVal;
}

bool UDS_DT_stopDataByPeriodicIdentifier(uint8_t *periodicDataIdentifiers, uint8_t periodicDataIdsLength, UDS_callback callback)
{
	if(periodicDataIdsLength == 0) return false;
	uint8_t message[2 + periodicDataIdsLength];
	message[0] = SID_ReadDataByPeriodicIdentifier;
	message[1] = 0x04;
	memcpy(&message[2], periodicDataIdentifiers, periodicDataIdsLength);
	return STM_Deploy(message, 2 + periodicDataIdsLength, callback, false);
}

bool UDS_DT_dynamicallyDefineDataIdentifierByDID(uint16_t definedDataIdentifier, DataDefinition *SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, UDS_callback callback)
{
	if (SourceDataDefinitionsLength == 0) return false;
	uint8_t message[4 + 4 * SourceDataDefinitionsLength];
	message[0] = SID_DynamicallyDefineDataIdentifier;
	message[1] = 0x01;
	message[2] = definedDataIdentifier >> 8;
	message[3] = definedDataIdentifier;
	for (uint32_t i = 0; i < SourceDataDefinitionsLength; i++)
	{
		message[4 + i * 4] = SourceDataDefinitions[i].DID >> 8;
		message[5 + i * 4] = SourceDataDefinitions[i].DID;
		message[6 + i * 4] = SourceDataDefinitions[i].firstBytePosition;
		message[7 + i * 4] = SourceDataDefinitions[i].memorySize;
	}
	return STM_Deploy(message, 4 + 4 * SourceDataDefinitionsLength, callback, false);
}

bool UDS_DT_dynamicallyDefineDataIdentifierByMemoryDefinition(uint16_t definedDataIdentifier, MemoryDefinition *SourceMemoryDefinitions, uint8_t SourceMemoryLength, UDS_callback callback)
{
	if(SourceMemoryLength == 0) return false;
	uint8_t message[4 + 4 * SourceMemoryLength];
	uint8_t addressLength = SourceMemoryDefinitions[0].AddressLength;
	uint8_t memoryLength = SourceMemoryDefinitions[0].SizeLength;
	message[0] = SID_DynamicallyDefineDataIdentifier;
	message[1] = 0x02;
	message[2] = definedDataIdentifier >> 8;
	message[3] = definedDataIdentifier;
	message[4] = MemoryDefinition_getAddressAndLengthFormatIdentifier(SourceMemoryDefinitions);
	for(uint32_t i = 0; i < SourceMemoryLength; i++) {
		memcpy(&message[5+i*(addressLength * memoryLength)], SourceMemoryDefinitions[i].Address, addressLength);
		memcpy(&message[5+i*(addressLength * memoryLength) + addressLength], SourceMemoryDefinitions[i].Size, memoryLength);
	}
	return STM_Deploy(message, 4 + 4 * SourceMemoryLength, callback, false);
}

bool UDS_DT_clearDynamicallyDefineDataIdentifier(uint16_t definedDataIdentifier, UDS_callback callback)
{
	uint8_t message[4];
	message[0] = SID_DynamicallyDefineDataIdentifier;
	message[1] = 0x03;
	message[2] = definedDataIdentifier >> 8;
	message[3] = definedDataIdentifier;
	return STM_Deploy(message, 4, callback, false);
}

bool UDS_DT_writeDataByIdentifier(uint16_t dataIdentifier, uint8_t *writeBuffer, uint8_t bufferLength, UDS_callback callback)
{
	uint8_t message[3 + bufferLength];
	message[0] = SID_WriteDataByIdentifier;
	message[1] = dataIdentifier >> 8;
	message[2] = dataIdentifier;
	memcpy(&message[3], writeBuffer, bufferLength);
	return STM_Deploy(message, 3 + bufferLength, callback, false);
}

bool UDS_DT_writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory, uint8_t *writeBuffer, uint8_t bufferLength, UDS_callback callback)
{
	uint32_t length = 2 + targetMemory.SizeLength + targetMemory.AddressLength + bufferLength;
	uint32_t i = 0;
	uint8_t message[length];
	message[i++] = SID_WriteDataByIdentifier;
	message[i++] = MemoryDefinition_getAddressAndLengthFormatIdentifier(&targetMemory);
	memcpy(&message[i], targetMemory.Address, targetMemory.AddressLength);
	i += targetMemory.AddressLength;
	memcpy(&message[i], targetMemory.Size, targetMemory.SizeLength);
	i += targetMemory.SizeLength;
	memcpy(&message[i], writeBuffer, bufferLength);
	return STM_Deploy(message, length, callback, false);
}