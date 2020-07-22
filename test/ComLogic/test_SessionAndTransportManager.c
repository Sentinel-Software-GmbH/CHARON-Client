#include "unity.h"
#include "SessionAndTransportManager.h"
#include <string.h>

/* COMINTERFACE MOCK */
static uint8_t* txBuffer;
static uint8_t txLength;
static uint8_t* rxBuffer;
static uint8_t rxLength;
static uint32_t Baudrate;
static bool initialized;

bool mock_init(void) { return initialized = true; }

bool mock_send(uint8_t* data, uint32_t length) {
    txBuffer = data;
    txLength = length;
    return true;
}
bool mock_receive(uint8_t* buffer, uint32_t length) {
    buffer = rxBuffer;
    length = rxLength;
    return true;
}
void mock_setSpeed(uint32_t baud) {
    Baudrate = baud;
}

/* TIMEINTERFACE MOCK */
#define TIMESTEP 100UL
static uint32_t current_time;

uint32_t mock_getTime(void) { 
    uint32_t tmp = current_time;
    current_time += TIMESTEP;
    return tmp;
}

uint32_t mock_diffTime(uint32_t this, uint32_t that) {
    uint32_t retVal = 0;
    if (this < that) {
        return UINT32_MAX - that + this;
    }
    return that - this;
}

/* static interfaces */
static ComInterface test_com = {mock_init, mock_send, mock_receive, mock_setSpeed};
static TimerInterface test_timer = {mock_getTime, mock_diffTime};
static uint8_t usr_rxBuffer[4096] = {0x00};

void setup(void) {
    current_time = 0;
    STM_Init(&test_com, &test_timer, &usr_rxBuffer, 4096);
    txBuffer = NULL;
    rxBuffer = NULL;
    rxLength = 0;
    txLength = 0;
    Baudrate = 9600;
}

void tearDown(void) {}

void test_Init_interfaces_should_be_correct_and_initialized(void) {  
    TEST_ASSERT_NOT_NULL(STM_getComInterface());
    TEST_ASSERT_NOT_NULL(STM_getTimerInterface());
    TEST_ASSERT_TRUE(initialized);
}

void test_Deploy_Message(void) {
    uint8_t* message = (uint8_t*)"This is a very long message buffer. It is so long, PCLint is complaining about the line length. To be fair PCLint really likes to bitch around.";
    uint32_t length = strlen((char*)message);
    TEST_ASSERT_EQUAL(E_OK, STM_Deploy(message, length, NULL, false));
    TEST_ASSERT_EQUAL_UINT8(length, txLength);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(message, txBuffer, length);
    TEST_ASSERT_EQUAL_CHAR('T', STM_getCurrentSID());
}

void test_Cyclic_Nothing_pending(void) {
    TEST_ASSERT_EQUAL(E_OK, STM_cyclic());
    // No KeepAlive should happen.
    TEST_ASSERT_EQUAL(0, txLength);
}

void test_change_Speed(void) {

}