/* COMINTERFACE MOCK */

#include <stdint.h>
#include <stdbool.h>

bool    test_com_init(void);
int32_t test_com_send(uint8_t *data, uint32_t length);
int32_t test_com_receive(uint8_t *buffer, uint32_t count);
bool    test_com_setSpeed(uint32_t baud);