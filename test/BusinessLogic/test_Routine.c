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
#include "Routine.h"
#include "DataModels/SID.h"
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

void test_StartRoutine(void) {
    TEST_MESSAGE("Testing the start of a routine.");
    uint8_t *expectedData = (uint8_t[]) {SID_RoutineControl, 0x01, 0x12, 0x34, 0xFF, 0xFF};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_ROUTINE_startRoutine(0x1234, (uint8_t[]) {0xFF, 0xFF}, 2, NULL));
    TEST_PASS_MESSAGE("This proves R21");
}

void test_StopRoutine(void) {
    TEST_MESSAGE("Testing the stop of a routine.");
    uint8_t *expectedData = (uint8_t[]) {SID_RoutineControl, 0x02, 0x12, 0x34};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_ROUTINE_stopRoutine(0x1234, NULL, 0, NULL));
    TEST_PASS_MESSAGE("This proves R21");
}

void test_RequestRoutineResults(void) {
    TEST_MESSAGE("Testing to request the routine results.");
    uint8_t *expectedData = (uint8_t[]) {SID_RoutineControl, 0x03, 0x12, 0x34};
    STM_Deploy_ExpectAndReturn(expectedData, 4, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_TRUE(UDS_ROUTINE_requestRoutineResults(0x1234, NULL));
    TEST_PASS_MESSAGE("This proves R21");
}
/*---************** (C) COPYRIGHT Sentinel Software GmbH *****END OF FILE*---*/