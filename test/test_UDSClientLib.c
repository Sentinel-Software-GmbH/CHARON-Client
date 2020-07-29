#include "unity.h"
#include "UDSClientLib.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_DiagnosticCommunicationManager.h"

void setUp(void) {
}
void tearDown(void) {}

void test_Init_success(void) {
    DCM_Init_ExpectAnyArgsAndReturn(true);
    STM_Init_ExpectAnyArgsAndReturn(true);
    TEST_ASSERT_EQUAL(true, UDS_Client_Init(NULL, NULL, NULL, NULL, 0));
}

void test_Init_STM_fails(void) {
    DCM_Init_ExpectAnyArgsAndReturn(true);
    STM_Init_ExpectAnyArgsAndReturn(false);
    TEST_ASSERT_EQUAL(false, UDS_Client_Init(NULL, NULL, NULL, NULL, 0));
}

void test_Init_DCM_fails(void) {
    DCM_Init_ExpectAnyArgsAndReturn(false);
    STM_Init_ExpectAnyArgsAndReturn(true);
    TEST_ASSERT_EQUAL(false, UDS_Client_Init(NULL, NULL, NULL, NULL, 0));
}

void test_switchSessionToDefault(void) {
    uint16_t p2 = 0x0100;
    uint16_t p2_star = 2560;
    DiagnosticSessionControl_ExpectAndReturn(UDS_Session_Default, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_Client_switchSession(UDS_Session_Default, NULL));
}