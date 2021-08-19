#pragma once

#include <stdint.h>


static inline void sleep(uint64_t ms) {
    ms <<= 12;

    for (uint64_t i = 0; i < ms; i++)
    {
        asm volatile ("nop;nop;nop");
    }
    
}
