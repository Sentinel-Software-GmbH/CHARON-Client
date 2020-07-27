#include "unity.h"
#include "BusinessLogic/DCM/DiagnosticCommunicationManager.h"
#include "mock_SessionAndTransportManager.h"
#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

void test_DiagnosticSessionControl(void) {
    uint16_t p2 = 256;
    uint16_t p2_star = 256;
    uint8_t *expectedData = (uint8_t[]){SID_DiagnosticSessionControl, UDS_Session_Programming, (p2 & 0xFF00) >> 8, (p2 & 0xFF), (p2_star & 0xFF00) >> 8, (p2_star & 0xFF)};
    STM_Deploy_ExpectAndReturn(expectedData, 6, NULL, false, true);
    TEST_ASSERT_EQUAL(true, DiagnosticSessionControl(UDS_Session_Programming, p2, p2_star * 10, NULL));
}

void test_ECUReset() {
    
}

bool ECUReset(uint8_t type);
bool SecurityAccess(uint8_t function, uint8_t *securityParameter, uint8_t parameterLength);
uint8_t SecuredDataTransmission(uint8_t* data, uint32_t length);
uint8_t ControlDTCSetting(uint8_t subfunction, uint8_t* data, uint32_t length);
uint8_t ResponseOnEvent(uint8_t event, bool storeEvent, uint8_t eventWindowTime, uint8_t eventTypeRecord[10], uint8_t serviceToRespondTo, uint8_t* serviceParameter);
void LinkControl();
bool DCM_Init(SecurityInterface_t *security);