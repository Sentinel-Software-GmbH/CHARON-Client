/**
 *  Sentinel Software GmbH
 *  Copyright (C) 2020 ${Author}
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
/*****************************************************************************/

/* TODO: Everything */

/* Includes ******************************************************************/

#include "unity.h"
#include "BusinessLogic/DataTransmitter/DataTransmitter.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_MemoryDefinition.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

/* Setup and Teardowns *******************************************************/

void setUp(void) {

}

void tearDown(void) {

}

/* Test Functions ************************************************************/

/* TODO: Everything */
void test_readDataByIdentifier(void) {
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadDataByIdentifier, 0x01, 0x34, 0x00, 0x27, 0x00, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 7, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readDataByIdentifier((uint16_t[]){0x0134, 0x0027, 0x0012}, 3, NULL));
}

/* TODO: Everything */
void test_readMemoryByAddress(void) {
    // TODO(inacio): later
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadMemoryByAdress,/*4, 4 */ 0b01000100, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78};
}

/* TODO: Everything */
void test_readScalingDataByIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_ReadDataByPeriodicIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_stopDataByPeriodicIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByDID(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByMemoryDefinition(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_clearDynamicallyDefineDataIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_writeDataByIdentifier(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_writeMemoryByAddress(void) {
    TEST_ASSERT_EQUAL(1, 1);
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/

/*
bool UDS_DT_readDataByIdentifier(uint16_t* dataIdentifier, uint8_t length, UDS_callback callback);
bool UDS_DT_readMemoryByAddress(MemoryDefinition sourceMemory, UDS_callback callback);
**
 * Very Complex. Might need the user to interpret the return values
 *
bool UDS_DT_readScalingDataByIdentifier(uint16_t dataIdentifier, UDS_callback callback);
bool UDS_DT_ReadDataByPeriodicIdentifier(UDS_TimerRates_t transmissionMode, uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdLength, UDS_callback callback, UDS_callback response_callback);
bool UDS_DT_stopDataByPeriodicIdentifier(uint8_t* periodicDataIdentifiers, uint8_t periodicDataIdsLength, UDS_callback callback);
** @brief Dynamically define a DataIdentifier.
 * If Both Lengths are 0, the Identifier will be cleared.
 * 
 * @param definedDataIdentifier Used to define a new DID.
 * @param SourceDataDefinitions Array of source DIDs, can be NULL.
 * @param SourceDataDefinitionsLength Length of the source DID array.
 * @param SourceMemoryDefinitions Array of memory
 *
bool UDS_DT_dynamicallyDefineDataIdentifier(uint16_t definedDataIdentifier, DataDefinition* SourceDataDefinitions, uint8_t SourceDataDefinitionsLength, MemoryDefinition* SourceMemoryDefinitions, uint8_t SourceMemoryLength, UDS_callback callback);
bool UDS_DT_writeDataByIdentifier(uint16_t dataIdentifier, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback);
bool UDS_DT_writeMemoryByAddress(uint16_t dataIdentifier, MemoryDefinition targetMemory, uint8_t* writeBuffer, uint8_t bufferLength, UDS_callback callback);
*/