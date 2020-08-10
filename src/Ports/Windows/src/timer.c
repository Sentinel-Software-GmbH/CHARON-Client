#include "Interfaces/TimerInterface.h"
#include <windows.h>

uint32_t getTime();
int64_t diffTime(uint32_t start, uint32_t stop);

TimerInterface timer1 = {
    getTime,
    diffTime
};

uint32_t getTime() {
    return GetTickCount();
}

int64_t diffTime(uint32_t start, uint32_t stop) {
    int64_t diff = stop;
    diff = diff - start;
    return diff;
}