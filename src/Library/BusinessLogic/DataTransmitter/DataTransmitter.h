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
 *  Created on: Tue Jul 28 2020
 */
/**
 * @addtogroup UDS_Client
 * @{
 * @defgroup BusinessLogic
 * @{
 * @file DataTransmitter.h
 * Collection of all configurable variables of the client.
 *
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */
/*****************************************************************************/

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

/** @brief Read out the value of a Data Identifier.
 * 
 * @param dataIdentifier List of DIDs you want to read out.
 * @param length Amount of entries in the list of DIDs.
 * @param callback Callback that gets executed when the service has finished.
 */
bool UDS_DT_readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, UDS_callback callback);

/** @brief Read out the values at the specified memory address
 * 
 * @param sourceMemory The address and size of the data in the servers memory.
 * @param callback Callback that gets executed when the service has finished.
 */
bool UDS_DT_readMemoryByAddress(MemoryDefinition sourceMemory, UDS_callback callback);
/** @brief Read out the scaling data pointed at by the specified DataIdentifier.
 * 
 * @todo Very Complex. Might need the user to interpret the return values or provide a function to decrypt the return value.
 * 
 * @param dataIdentifier Data identifier of the scaling data.
 * @param callback Callback that gets executed when the service has finished.
 */
bool UDS_DT_readScalingDataByIdentifier(uint16_t dataIdentifier, UDS_callback callback);
/** @brief Set up a periodic polling of the specified DIDs at a fixed speed defined by the server.
 * 
 * @note When you set up too many DIDs the server might not be able to respond at its fixed speed.
 * Check ISO 14229-1 Chapter 10.5 for an explanation.
 * 
 * @param transmissionMode Slow/Medium/Fast Rate at which the data will be read.
 * @param periodicDataIdentifiers A List of DIDs to set up for periodic polling.<br>
 * Periodic DIDs only have 8-bit length, because only 0xF2XX DIDs can be polled periodically.
 * @param periodicDataIdLength Amount of entries in the DID list.
 * @param callback Callback that gets executed when the service request has finished.
 * @param callback Callback that gets executed when a response has been received.
 */
bool UDS_DT_ReadDataByPeriodicIdentifier(UDS_TimerRates_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength, UDS_callback callback, UDS_callback response_callback);

/** @brief Stop any periodic poll set up of the specified DIDs.
 * 
 * @param periodicDataIdentifiers A List of periodic DIDs to set up for periodic polling.
 * @param periodicDataIdsLength Amount of entries in the DID list.
 * @param callback Callback that gets executed when the service request has finished.
 */ 
bool UDS_DT_stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength, UDS_callback callback);
/** @brief Dynamically define a DataIdentifier.
 * If Both Lengths are 0, the Identifier will be cleared.
 * 
 * @param definedDataIdentifier Used to define a new DID.
 * @param SourceDataDefinitions Array of source DIDs, can be NULL.
 * @param SourceDataDefinitionsLength Length of the source DID array.
 * @param SourceMemoryDefinitions Array of memory
 */
bool UDS_DT_dynamicallyDefineDataIdentifierByDID(uint16_t definedDataIdentifier, DataDefinition *SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, UDS_callback callback);
bool UDS_DT_dynamicallyDefineDataIdentifierByMemoryDefinition(uint16_t definedDataIdentifier, MemoryDefinition *SourceMemoryDefinitions, uint8_t SourceMemoryLength, UDS_callback callback);
bool UDS_DT_clearDynamicallyDefineDataIdentifier(uint16_t definedDataIdentifier, UDS_callback callback);
bool UDS_DT_writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback);
bool UDS_DT_writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback);


#ifdef __cplusplus
}
#endif


#endif /*!defined(EA_B5D43F1B_EA2F_4dd9_ADDA_89D31FE79F42__INCLUDED_)*/
 