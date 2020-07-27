#ifndef _TEST_TIME_H_
#define _TEST_TIME_H_

#include <stdint.h>

uint32_t time_getTime(void);

int32_t time_diffTime(uint32_t _this, uint32_t _that);

#endif