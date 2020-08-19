#include "unity.h"
#include "UDSClientLib.h"
#include "mock_SessionAndTransportManager.h"
#include "mock_DiagnosticCommunicationManager.h"

void setUp(void) {
}
void tearDown(void) {}

void test_Init_success(void) {
    STM_Init_ExpectAnyArgs();
    UDS_Client_Init(NULL, NULL, NULL, NULL, 0);
}