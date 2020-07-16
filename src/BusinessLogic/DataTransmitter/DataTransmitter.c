/****************************************************
 *  DataTransmitter.c                                         
 *  Created on: 16-Jul-2020 09:29:59                      
 *  Implementation of the Class DataTransmitter       
 *  Original author: Steven Inacio                     
 ****************************************************/

#include "DataTransmitter.h"
#include <stdint.h>

uint8_t readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, uint8_t buffer)
{
	return  NULL;
}

uint8_t readMemoryByAddress(MemoryDefinition sourceMemory, uint8_t buffer)
{
	return  NULL;
}

/**
 * Very Complex. Might need the user to interpret the return values
 */
uint8_t readScalingDataByIdentifier(uint16_t dataIdentifier, uint8_t buffer)
{
	return  NULL;
}

uint8_t controlReadDataByPeriodicIdentifier(uint8_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength)
{
	return  NULL;
}

void readDataByPeriodicIdentifier(uint8_t buffer)
{
	
}

void stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength)
{
	
}

/**
 * If Both Lengths are 0, the Identifier will be cleared.
 */
void dynamicallyDefineDataIdentifier(uin16_t definedDataIdentifier, DataDefinition* SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, MemoryDefinition* SourceMemoryDefinitions, uint8_t SourceMemoryLength)
{
	
}

void writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength)
{
	
}

void writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory)
{
	
} 

