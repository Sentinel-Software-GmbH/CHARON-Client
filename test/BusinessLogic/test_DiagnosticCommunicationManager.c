#include "unity.h"
#include "BusinessLogic/DCM/DiagnosticCommunicationManager.h"
#include "mock_SessionAndTransportManager.h"
#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

void test_DiagnosticSessionControl(void) {
    uint8_t *expectedData = (uint8_t[]){SID_DiagnosticSessionControl, UDS_Session_Programming};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DCM_DiagnosticSessionControl(UDS_Session_Programming, NULL));
}

void test_ECUReset() {
    uint8_t* expectedData = (uint8_t[]){SID_ECUReset, UDS_HardReset};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DCM_ECUReset(UDS_HardReset, NULL));
}

void test_SecurityAccess() {
    uint8_t* expectedData = (uint8_t[]) {SID_SecurityAccess, 0x05, 0xDE, 0xAD, 0xC0, 0xDE};
    uint8_t* securityParameter = (uint8_t[]) {0xDE, 0xAD, 0xC0, 0xDE};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
 
    TEST_ASSERT_EQUAL(true, UDS_DCM_SecurityAccess(0x05, securityParameter, 4, NULL));
}

void test_ControlDTCSetting() {
    uint8_t* expectedData = (uint8_t[]) {SID_ControlDTCSettings, 0x01, 0x00, 0x01, 0x02, 0x03};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    uint8_t* DTCdata = (uint8_t[]) {0x00, 0x01, 0x02, 0x03};
    TEST_ASSERT_EQUAL(true, UDS_DCM_ControlDTCSetting(0x01, DTCdata, 4, NULL));
}

void test_ResponseOnEvent() {}

void test_LinkControl() {}

void test_DCM_Init() {
}
