#include "unity.h"
#include "UDSClientLib.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_DiagnosticCommunicationManager.h"

void setUp(void) {
    UDS_Client_Init(NULL, NULL, NULL, NULL, 0);
}
void tearDown(void) {}

void test_switchSessionToDefault(void) {
    uint16_t p2 = 0x0010;
    uint16_t p2_star = 0x0010;
    UDS_Client_switchSession(UDS_Session_Default, p2, p2_star, NULL);
}