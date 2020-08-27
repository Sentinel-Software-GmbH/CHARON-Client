/*
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
/**
 * @addtogroup UDS_Client
 * @{
 * @addtogroup TestModules
 * @{
 * @file
 * Data Transmitter Module.
 * 
 * $Id:  $
 * $URL:  $
 * @}
 * @}
 */

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

/** Definition of a DID */
static const DataDefinition dataDef = {
    .DID = 0x0134,
    .firstBytePosition = 0x04,
    .memorySize = 0x10,
};

/** Definition of a Memory Range on the server */
static const MemoryDefinition memDef = {
    .Address = (uint8_t[]){0x43, 0x21},
    .Size = (uint8_t[]){0x00, 0x10},
    .AddressLength = 2,
    .SizeLength = 2,
};

/** Test Data */
static const uint8_t data[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

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
    TEST_MESSAGE("Testing the correct construction of a Read Data by Identifier Request.");
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadDataByIdentifier, 0x01, 0x34, 0x00, 0x27, 0x00, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 7, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readDataByIdentifier((uint16_t[]){0x0134, 0x0027, 0x0012}, 3, NULL));
    TEST_PASS_MESSAGE("This proves R11");
}

void test_readMemoryByAddress(void)
{
    TEST_MESSAGE("Testing the correct construction of a Read Memory by Address request.");
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadMemoryByAddress, /*4, 4 */ 0b01000100, 0x43, 0x21, 0x00, 0x10};
    MemoryDefinition_getAddressAndLengthFormatIdentifier_ExpectAndReturn(&memDef, 0x22);
    STM_Deploy_ExpectAndReturn(expectedMessage, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readMemoryByAddress(memDef, NULL));
    TEST_PASS_MESSAGE("This proves R12");
}

void test_readScalingDataByIdentifier(void)
{
    TEST_MESSAGE("Testing the correct construction of a read scaling data by identifier request.");
    uint8_t *expectedMessage = (uint8_t[]){SID_ReadScalingDataByIdentifier, 0x12, 0x34};
    STM_Deploy_ExpectAndReturn(expectedMessage, 3, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_readScalingDataByIdentifier(0x1234, NULL));
    TEST_PASS_MESSAGE("This proves R13");
}

void test_ReadDataByPeriodicIdentifier(void)
{
    TEST_MESSAGE("Testing the correct construction of a read data by periodic identifier request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadDataByPeriodicIdentifier, 0x01, 0x23, 0x53, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByPeriodicIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DT_ReadDataByPeriodicIdentifier(UDS_SlowTimer, (uint8_t[]) {0x23, 0x53, 0x12}, 3, NULL, NULL));
    TEST_PASS_MESSAGE("This proves R14");
}

/* TODO: Everything */
void test_stopDataByPeriodicIdentifier(void)
{
    TEST_MESSAGE("Testing the correct construction of a stop data by periodic identifier request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_ReadDataByPeriodicIdentifier, 0x04, 0x23, 0x53, 0x12};
    STM_Deploy_ExpectAndReturn(expectedMessage, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DT_stopDataByPeriodicIdentifier((uint8_t[]) {0x23, 0x53, 0x12}, 3, NULL));
    TEST_PASS_MESSAGE("This proves R14");
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByDID(void)
{
    TEST_MESSAGE("Testing the correct construction of a dynamically defined data by a data identifier request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_DynamicallyDefineDataIdentifier, 0x01, 0xF2, 0x66, 0x01, 0x34, 0x04, 0x10};
    STM_Deploy_ExpectAndReturn(expectedMessage, 8, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DT_dynamicallyDefineDataIdentifierByDID(0xF266, &dataDef, 1, NULL));
    TEST_PASS_MESSAGE("This proves R15");
}

/* TODO: Everything */
void test_dynamicallyDefineDataIdentifierByMemoryDefinition(void)
{
    TEST_MESSAGE("Testing the correct construction of a dynamically defined data by a memory address definition request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_DynamicallyDefineDataIdentifier, 0x02, 0xF3, 0x66, 0x22, 0x43, 0x21, 0x00, 0x10};
    MemoryDefinition_getAddressAndLengthFormatIdentifier_ExpectAndReturn(&memDef, 0x22);
    STM_Deploy_ExpectAndReturn(expectedMessage, 9, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DT_dynamicallyDefineDataIdentifierByMemoryDefinition(0xF266, &memDef, 1, NULL));
    TEST_PASS_MESSAGE("This proves R15");
}

/* TODO: Everything */
void test_clearDynamicallyDefineDataIdentifier(void)
{
    TEST_MESSAGE("Testing the correct construction of a clear dynamically defined data request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_DynamicallyDefineDataIdentifier, 0x03, 0xF2, 0x66};
    STM_Deploy_ExpectAndReturn(expectedMessage, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DT_clearDynamicallyDefineDataIdentifier(0xF266, NULL));
    TEST_PASS_MESSAGE("This proves R15");
}

/* TODO: Everything */
void test_writeDataByIdentifier(void)
{
    TEST_MESSAGE("Testing the correct construction of a write data by identifier request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_WriteDataByIdentifier, 0x01, 0x34, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedMessage, 19, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DT_writeDataByIdentifier(0x0134, data, 16, NULL));
    TEST_PASS_MESSAGE("This proves R16");
}

/* TODO: Everything */
void test_writeMemoryByAddress(void)
{
    TEST_MESSAGE("Testing the correct construction of a write memory by address request.");
    uint8_t *expectedMessage = (uint8_t[]) {SID_WriteMemoryByAdress, 0x22, 0x43, 0x21, 0x00, 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    MemoryDefinition_getAddressAndLengthFormatIdentifier_ExpectAndReturn(&memDef, 0x22);
    STM_Deploy_ExpectAndReturn(expectedMessage, 22, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_DT_writeMemoryByAddress(memDef, data, 16, NULL));
    TEST_PASS_MESSAGE("This proves R17");
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/
