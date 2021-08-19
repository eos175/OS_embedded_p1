#pragma once

#include <stdint.h>
#include <mtwister.h>


void random_init(uint64_t seed);

// randint(0, 10) -> 0 .. 10
int64_t randint(int64_t a, int64_t b);
