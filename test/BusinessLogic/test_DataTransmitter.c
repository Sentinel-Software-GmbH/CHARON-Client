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

#include "BusinessLogic/DataTransmitter/DataTransmitter.h"
#include "DataModels/SID.h"
#include "mock_MemoryDefinition.h"
#include "mock_SessionAndTransportManager.h"
#include "unity.h"

/* Imports *******************************************************************/

/* Constants *****************************************************************/

/* Macros ********************************************************************/

/* Types *********************************************************************/

/* Variables *****************************************************************/

static const DataDefinition dataDef = {
    .DID = 0x0134,
    .firstBytePosition = 0x04,
    .memorySize = 0x10,
};

static const MemoryDefinition memDef = {
    .Address = (uint8_t[]){0x43, 0x21},
    .Size = (uint8_t[]){0x00, 0x10},
    .AddressLength = 2,
    .SizeLength = 2,
};

/* Setup and Teardowns *******************************************************/

void setUp(void)
{
}

void tearDown(void)
{
}

/* Test Functions ************************************************************/

void test_readDataByIdentifier(void)
{
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadDataByIdentifier, 0x01, 0x34, 0x00, 0x27, 0x00, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 7, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readDataByIdentifier((uint16_t[]){0x0134, 0x0027, 0x0012}, 3, NULL));
}

void test_readMemoryByAddress(void)
{
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadMemoryByAdress, /*4, 4 */ 0b01000100, 0x43, 0x21, 0x00, 0x10};
    STM_Deploy_ExpectAndReturn(expectedMessage, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readMemoryByAddress(memDef, NULL));
}

void test_readScalingDataByIdentifier(void)
{
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadScalingDataByIdentifier, 0x12, 0x34};
    STM_Deploy_ExpectAndReturn(expectedMessage, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readScalingDataByIdentifier(0x1234, NULL));
}

void test_ReadDataByPeriodicIdentifier(void)
{
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadDataByPeriodicIdentifier, 0x01, 0x23, 0x53, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByPeriodicIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DT_ReadDataByPeriodicIdentifier(UDS_SlowTimer, (uint8_t[]) {0x23, 0x53, 0x12}, 3, NULL, NULL));
}

/* TODO: Everything */
void test_stopDataByPeriodicIdentifier(void)
{
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadDataByPeriodicIdentifier, 0x04, 0x23, 0x53, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_stopDataByPeriodicIdentifier((uint8_t[]) {0x23, 0x53, 0x12}, 3, NULL));
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByDID(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByMemoryDefinition(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_clearDynamicallyDefineDataIdentifier(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_writeDataByIdentifier(void)
{
    TEST_ASSERT_EQUAL(1, 1);
}

/* TODO: Everything */
void test_writeMemoryByAddress(void)
{
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