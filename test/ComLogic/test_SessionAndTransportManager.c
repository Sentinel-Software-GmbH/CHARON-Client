
#include "unity.h"
#include "SessionAndTransportManager.h"
#include "DataModels/SID.h"
#include <string.h>
#include "config.h"
#include "mock_TestCom.h"
#include "mock_TestTime.h"
#include "mock_TestSecurity.h"


/* static interfaces */
static ComInterface test_com = {test_com_send, test_com_receive, test_com_setSpeed, true};
static TimerInterface test_timer = {time_getTime, time_diffTime};
static SecurityInterface test_security = { test_encrypt, test_decrypt };
static uint8_t usr_rxBuffer[4096] = {0x00};

void callback(UDS_Client_Error_t error, uint8_t *buffer, uint32_t length);

void setup(void) {
}

void tearDown(void) {

}

void test_Init_interfaces_should_be_correct_and_initialized(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    TEST_ASSERT_NOT_NULL(STM_getComInterface());
    TEST_ASSERT_NOT_NULL(STM_getTimerInterface());
}

void test_Deploy_Message(void) {
    setup();
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t* message = (uint8_t*)"This is a very long message buffer. It is so long, PCLint is complaining about the line length. To be fair PCLint really likes to bitch around.";
    int32_t length = strlen(message);
    test_com_send_ExpectAndReturn(message, length, length);
    time_getTime_ExpectAndReturn(0);
    TEST_ASSERT_EQUAL(true, STM_Deploy(message, length, NULL, false));
    TEST_ASSERT_EQUAL_CHAR('T', STM_getCurrentSID());
}

void test_Cyclic_Nothing_pending(void) {
    test_com_receive_IgnoreAndReturn(0);
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Cyclic_Pending_Timeout(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_send_ExpectAndReturn(expectedData, 6, 6);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    test_com_receive_ExpectAnyArgsAndReturn(0);
    time_getTime_ExpectAndReturn(110);
    time_diffTime_ExpectAndReturn(100, 110, 10);
    TEST_ASSERT_EQUAL(E_NotResponding, STM_cyclic());
}

void test_Cyclic_Pending_WrongAnswer(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, 6);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x7F, 0x20};
    test_com_receive_ExpectAnyArgsAndReturn(2);
    test_com_receive_ReturnThruPtr_buffer(receiveData);
    TEST_ASSERT_EQUAL(E_NegativeResponse, STM_cyclic());
}

void test_Cyclic_Pending_CorrectAnswer(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, 6);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x50, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_receive_ExpectAnyArgsAndReturn(6);
    test_com_receive_ReturnMemThruPtr_buffer(receiveData, 6);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Cyclic_Pending_AnswerPending_Timeout(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, 6);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){SID_NEGATIVE_RESPONSE, 0x10, 0x78};
    test_com_receive_ExpectAnyArgsAndReturn(3);
    test_com_receive_ReturnMemThruPtr_buffer(receiveData, 3);
    time_getTime_ExpectAndReturn(50);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    test_com_receive_IgnoreAndReturn(0);
    time_getTime_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-250L);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(10);
    TEST_ASSERT_EQUAL(E_NotResponding, STM_cyclic());
}

void test_Cyclic_Pending_AnswerReceived() {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){SID_DiagnosticSessionControl, UDS_Session_Default, 0x00, 0x34, 0x00, 0x34};
    test_com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, 6);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){SID_NEGATIVE_RESPONSE, 0x10, 0x78};
    test_com_receive_ExpectAnyArgsAndReturn(3);
    test_com_receive_ReturnMemThruPtr_buffer(receiveData, 3);
    time_getTime_ExpectAndReturn(50);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    test_com_receive_ExpectAnyArgsAndReturn(0);
    time_getTime_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-250);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    receiveData = (uint8_t[]){0x50, 0x01, 0x00, 0x34, 0x00, 0x34};
    test_com_receive_ExpectAnyArgsAndReturn(6);
    test_com_receive_ReturnThruPtr_buffer(receiveData);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Switch_Session_Keep_Alive(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    STM_SetSession(UDS_Session_Extended, 100, 300);
    uint8_t expectedData[2] = { SID_TesterPresent, 0x80 };
    time_getTime_IgnoreAndReturn(0);
    test_com_receive_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-1L);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(500L);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(2150L);
    test_com_send_ExpectAndReturn(expectedData, 2, 2);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_SetSessionTiming(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    UDS_Session_t expected = (UDS_Session_t){UDS_Session_Default, 100, 1000};
    STM_SetSession(0, 100, 1000);
    UDS_Session_t session = STM_getCurrentSession();
    TEST_ASSERT_EQUAL(expected.session, session.session);
    TEST_ASSERT_EQUAL(expected.p2, session.p2);
    TEST_ASSERT_EQUAL(expected.p2_star, session.p2_star);
}
void test_SetSessionExtended(void) {
    STM_Init(&test_com, &test_timer, &test_security, (uint8_t * const)usr_rxBuffer, 4096);
    UDS_Session_t expected = (UDS_Session_t){UDS_Session_Extended, 50, 5000};
    STM_SetSession(UDS_Session_Extended, 50, 5000);
    UDS_Session_t session = STM_getCurrentSession();
    TEST_ASSERT_EQUAL(expected.session, session.session);
    TEST_ASSERT_EQUAL(expected.p2, session.p2);
    TEST_ASSERT_EQUAL(expected.p2_star, session.p2_star);
}