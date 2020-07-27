#include "unity.h"
#include "SessionAndTransportManager.h"
#include "DataModels/SID.h"
#include <string.h>
#include "mock_TestCom.h"
#include "mock_TestTime.h"


/* static interfaces */
static ComInterface test_com = {com_init, com_send, com_receive, com_setSpeed};
static TimerInterface test_timer = {time_getTime, time_diffTime};
static uint8_t usr_rxBuffer[4096] = {0x00};

void callback(UDS_Client_Error_t error, uint8_t *buffer, uint32_t length);

void setup(void) {
}

void tearDown(void) {
}

void test_Init_interfaces_should_be_correct_and_initialized(void) {
    com_init_ExpectAndReturn(true);
    TEST_ASSERT_EQUAL(true, STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096));
    TEST_ASSERT_NOT_NULL(STM_getComInterface());
    TEST_ASSERT_NOT_NULL(STM_getTimerInterface());
}

void test_Deploy_Message(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t* message = (uint8_t*)"This is a very long message buffer. It is so long, PCLint is complaining about the line length. To be fair PCLint really likes to bitch around.";
    uint32_t length = strlen(message);
    com_send_ExpectWithArrayAndReturn(message, length, length, true);
    time_getTime_ExpectAndReturn(0);
    TEST_ASSERT_EQUAL(true, STM_Deploy(message, length, NULL, false));
    TEST_ASSERT_EQUAL_CHAR('T', STM_getCurrentSID());
}

void test_Cyclic_Nothing_pending(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Cyclic_Pending_Timeout(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, true);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    com_receive_ExpectAnyArgsAndReturn(0);
    time_getTime_ExpectAndReturn(110);
    time_diffTime_ExpectAndReturn(100, 110, 10);
    TEST_ASSERT_EQUAL(E_NotResponding, STM_cyclic());
}

void test_Cyclic_Pending_WrongAnswer(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, true);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x7F, 0x20};
    com_receive_ExpectAnyArgsAndReturn(2);
    com_receive_ReturnThruPtr_buffer(receiveData);
    TEST_ASSERT_EQUAL(E_NegativeResponse, STM_cyclic());
}

void test_Cyclic_Pending_CorrectAnswer(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, true);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x50, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_receive_ExpectAnyArgsAndReturn(6);
    com_receive_ReturnThruPtr_buffer(receiveData);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Cyclic_Pending_AnswerPending_Timeout(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){0x10, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, true);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x78, 0x10};
    com_receive_ExpectAnyArgsAndReturn(2);
    com_receive_ReturnThruPtr_buffer(receiveData);
    time_getTime_ExpectAndReturn(50);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    com_receive_IgnoreAndReturn(0);
    time_getTime_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-250);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(10);
    TEST_ASSERT_EQUAL(E_NotResponding, STM_cyclic());
}

void test_Cyclic_Pending_AnswerReceived() {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    uint8_t *expectedData = (uint8_t[]){SID_DiagnosticSessionControl, UDS_Session_Default, 0x00, 0x34, 0x00, 0x34};
    com_send_ExpectWithArrayAndReturn(expectedData, 6, 6, true);
    time_getTime_ExpectAndReturn(0);
    STM_Deploy(expectedData, 6, NULL, false);
    uint8_t *receiveData = (uint8_t[]){0x78, 0x10};
    com_receive_ExpectAnyArgsAndReturn(2);
    com_receive_ReturnThruPtr_buffer(receiveData);
    time_getTime_ExpectAndReturn(50);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    com_receive_ExpectAnyArgsAndReturn(0);
    time_getTime_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-250);
    TEST_ASSERT_EQUAL(E_Pending, STM_cyclic());
    receiveData = (uint8_t[]){0x50, 0x01, 0x00, 0x34, 0x00, 0x34};
    com_receive_ExpectAnyArgsAndReturn(6);
    com_receive_ReturnThruPtr_buffer(receiveData);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
}

void test_Switch_Session_Keep_Alive(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    STM_SetSession(UDS_Session_Extended, 100, 300);
    uint8_t expectedData[2] = { SID_TesterPresent, 0x80 };
    time_getTime_IgnoreAndReturn(0);
    time_diffTime_ExpectAnyArgsAndReturn(-1);
    com_send_ExpectAndReturn(expectedData, 2, true);
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(500);
    printf("Before second cyclic");
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    time_diffTime_ExpectAnyArgsAndReturn(1150);
    com_send_ExpectAndReturn(expectedData, 2, true);
    printf("Before third cyclic");
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    printf("After third cyclic");
}

void test_SetSessionTiming(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    UDS_Session_t expected = (UDS_Session_t){UDS_Session_Default, 100, 1000};
    STM_SetSession(0, 100, 1000);
    UDS_Session_t session = STM_getCurrentSession();
    TEST_ASSERT_EQUAL(expected.session, session.session);
    TEST_ASSERT_EQUAL(expected.p2, session.p2);
    TEST_ASSERT_EQUAL(expected.p2_star, session.p2_star);
}
void test_SetSessionExtended(void) {
    com_init_ExpectAndReturn(true);
    STM_Init(&test_com, &test_timer, (uint8_t * const)usr_rxBuffer, 4096);
    UDS_Session_t expected = (UDS_Session_t){UDS_Session_Extended, 50, 5000};
    STM_SetSession(UDS_Session_Extended, 50, 5000);
    UDS_Session_t session = STM_getCurrentSession();
    TEST_ASSERT_EQUAL(expected.session, session.session);
    TEST_ASSERT_EQUAL(expected.p2, session.p2);
    TEST_ASSERT_EQUAL(expected.p2_star, session.p2_star);
}