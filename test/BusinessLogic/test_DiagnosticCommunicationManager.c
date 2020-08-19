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

void test_ResponseOnEvent() {
    uint8_t* expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x06};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, UDS_DCM_ClearResponseOnEvents(NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x01, 0x02, 0xFF, SID_ReadDataByIdentifier, 0x00, 0x01};
    STM_Deploy_ExpectAndReturn(expectedData, 7, NULL, false, true);
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_ResponseOnDTCStatusChange(false, 0x02, 0xFF, SID_ReadDataByIdentifier, (uint8_t[]){0x00, 0x01}, 2, NULL, NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x42, 0x02, UDS_SlowTimer, SID_ReadDataByIdentifier, 0x00, 0x01};
    STM_Deploy_ExpectAndReturn(expectedData, 7, NULL, false, true);
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_ResponseOnTimerInterrupt(true, 0x02, UDS_SlowTimer, SID_ReadDataByIdentifier, (uint8_t[]) {0x00, 0x01}, 2, NULL, NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x03, 0x02, 0x00, 0x01, SID_ReadDataByIdentifier, 0x00, 0x01};
    STM_Deploy_ExpectAndReturn(expectedData, 8, NULL, false, true);
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_ResponseOnChangeOfDataIdentifier(false, 0x02, 0x0001, SID_ReadDataByIdentifier, (uint8_t[]) {0x00, 0x01}, 2, NULL, NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x07, 0x02, 0x00, 0x01, CompLogic_Equal, 0x00, 0x00, 0x10, 0x10, 0x0A, 0x82, 0xA5, SID_ReadDataByIdentifier, 0x00, 0x02};
    STM_Deploy_ExpectAndReturn(expectedData, 16, NULL, false, true);
    STM_AsyncDeploy_ExpectAndReturn(SID_ReadDataByIdentifier, NULL, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_ResponseOnComparisonOfValues(false, 0x02, 0x0001, CompLogic_Equal, 0x00001010, 10, true, 32, 0x02A5, SID_ReadDataByIdentifier, 0x0002, NULL, NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x05};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_StartResponseOnEvents(NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x00};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_StopResponseOnEvents(NULL));
    expectedData = (uint8_t[]) {SID_ResponseOnEvent, 0x04};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_GetActiveResponseEvents(NULL));
}

void test_LinkControl() {
    // Speed is not adjustable
    STM_SpeedIsAdjustable_ExpectAndReturn(false);
    TEST_ASSERT_EQUAL(false, UDS_DCM_LinkControl_verifyWithFixedParameter(UDS_Baud_PC9600, NULL));
    STM_SpeedIsAdjustable_ExpectAndReturn(false);
    TEST_ASSERT_EQUAL(false, UDS_DCM_LinkControl_verifyWithSpecificParameter(9600, NULL));
    // Speed is adjustable
    STM_SpeedIsAdjustable_IgnoreAndReturn(true);
    uint8_t *expectedData = (uint8_t[]) {SID_LinkControl, 0x01, 0x01};
    STM_Deploy_ExpectAndReturn(expectedData, 3, NULL, false, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_LinkControl_verifyWithFixedParameter(UDS_Baud_PC9600, NULL));
    expectedData = (uint8_t[]) {SID_LinkControl, 0x02, 0x00, 0x25, 0x80};
    STM_Deploy_ExpectAndReturn(expectedData, 5, NULL, false, true);
    TEST_ASSERT_EQUAL(true, UDS_DCM_LinkControl_verifyWithSpecificParameter(9600, NULL));
}

void test_DCM_Init() {
}
