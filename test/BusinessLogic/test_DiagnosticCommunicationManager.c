#include "unity.h"
#include "BusinessLogic/DCM/DiagnosticCommunicationManager.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_TestSecurity.h"
#include <stdbool.h>

static SecurityInterface security = (SecurityInterface) {encrypt, decrypt};

void setUp(void) {}
void tearDown(void) {}

void test_DiagnosticSessionControl(void) {
    uint8_t *expectedData = (uint8_t[]){SID_DiagnosticSessionControl, UDS_Session_Programming};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, DiagnosticSessionControl(UDS_Session_Programming, NULL));
}

void test_ECUReset() {
    uint8_t* expectedData = (uint8_t[]){SID_ECUReset, UDS_HardReset};
    STM_Deploy_ExpectAndReturn(expectedData, 2, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, ECUReset(UDS_HardReset, NULL));
}

void test_SecurityAccess() {
    uint8_t* expectedData = (uint8_t[]) {SID_SecurityAccess, 0x05, 0xDE, 0xAD, 0xC0, 0xDE};
    uint8_t* securityParameter = (uint8_t[]) {0xDE, 0xAD, 0xC0, 0xDE};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, SecurityAccess(0x05, securityParameter, 4, NULL));
}

void test_SecuredDataTransmission() {
    TEST_ASSERT_EQUAL(true, DCM_Init(&security));
    uint8_t* expectedData = (uint8_t[]) {SID_SecuredDataTransmission, 0xDE, 0xAD, 0xC0, 0xDE };
    uint8_t* unsecureData = (uint8_t[]) {0xC0, 0xAD, 0xDE, 0xDE};
    uint8_t* securedData = (uint8_t[]) {0xDE, 0xAD, 0xC0, 0xDE};
    encrypt_ExpectAndReturn(unsecureData, 4, securedData);
    STM_Deploy_ExpectAndReturn(expectedData, 5, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    TEST_ASSERT_EQUAL(true, SecuredDataTransmission(unsecureData, 4, NULL));
}
void test_SecuredDataTransmission_NoSecurityInterface() {
    TEST_ASSERT_EQUAL(true, DCM_Init(NULL));
    uint8_t* unsecureData = (uint8_t[]) {0xC0, 0xAD, 0xDE, 0xDE};
    TEST_ASSERT_EQUAL(false, SecuredDataTransmission(unsecureData, 4, NULL));
}

void test_ControlDTCSetting() {
    uint8_t* expectedData = (uint8_t[]) {SID_ControlDTCSettings, 0x01, 0x00, 0x01, 0x02, 0x03};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    STM_Deploy_IgnoreArg_callback();
    uint8_t* DTCdata = (uint8_t[]) {0x00, 0x01, 0x02, 0x03};
    TEST_ASSERT_EQUAL(true, ControlDTCSetting(0x01, DTCdata, 4, NULL));
}

void test_ResponseOnEvent() {}

void test_LinkControl() {}

void test_DCM_Init() {
    TEST_ASSERT_EQUAL(true, DCM_Init(NULL));
}
