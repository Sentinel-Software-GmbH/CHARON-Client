/* COMINTERFACE MOCK */

#include <stdint.h>
#include <stdbool.h>

bool com_init(void);
bool com_send(uint8_t *data, uint32_t length);
uint32_t com_receive(uint8_t *buffer, uint32_t count);
void com_setSpeed(uint32_t baud);