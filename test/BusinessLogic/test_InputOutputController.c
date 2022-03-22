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

/* Includes ******************************************************************/

#include "unity.h"
#include "DataModels/SID.h"
#include "BusinessLogic/IOControl/InputOutputController.h"
#include "mock_SessionAndTransportManager.h"

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

void test_ReturnControlToECU(void) {
    TEST_MESSAGE("This tests the return control to the ecu part of the IOControlByIdentifier.");
    uint8_t *expectedData = (uint8_t[]) {SID_InputOutputControlByIdentifier, 0x12, 0x34, 0x00, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_IO_ReturnControlToECU(0x1234, (uint8_t[]){0xFF}, 1, NULL));
    TEST_PASS_MESSAGE("This proves R21.");
}

void test_ResetToDefault(void) {
    TEST_MESSAGE("This tests the reset to default part of the IOControlByIdentifier.");
    uint8_t *expectedData = (uint8_t[]) {SID_InputOutputControlByIdentifier, 0x12, 0x34, 0x01};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_IO_ResetToDefault(0x1234, NULL, 0, NULL));
    TEST_PASS_MESSAGE("This proves R21.");
}

void test_FreezeCurrentState(void) {
    TEST_MESSAGE("This tests the freezing of the current state part of the IOControlByIdentifier.");
    uint8_t *expectedData = (uint8_t[]) {SID_InputOutputControlByIdentifier, 0x12, 0x34, 0x02, 0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA};
    STM_Deploy_ExpectAndReturn(expectedData, 10, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_IO_FreezeCurrentState(0x1234, (uint8_t[]) {0xFF, 0xAA, 0xFF, 0xAA, 0xFF, 0xAA}, 6, NULL));
    TEST_PASS_MESSAGE("This proves R21.");
}

void test_ShortTermAdjustments(void) {
    TEST_MESSAGE("This tests the short term adjustments part of the IOControlByIdentifier.");
    uint8_t *expectedData = (uint8_t[]) {SID_InputOutputControlByIdentifier, 0x12, 0x34, 0x03, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    STM_Deploy_ExpectAndReturn(expectedData, 12, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_IO_ShortTermAdjustment(0x1234, (uint8_t[]) {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88}, 8, NULL, 0, NULL));
    TEST_PASS_MESSAGE("This proves R21.");
}

/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/