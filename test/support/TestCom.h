/* COMINTERFACE MOCK */

#include <stdint.h>
#include <stdbool.h>

bool com_init(void);
int32_t com_send(uint8_t *data, uint32_t length);
int32_t com_receive(uint8_t *buffer, uint32_t count);
bool com_setSpeed(uint32_t baud);