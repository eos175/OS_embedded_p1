#pragma once

#include <stdint.h>
#include <mtwister.h>



static MTRand _rand;


static void random_init(uint64_t seed)
{
    _rand = seedRand(seed);
}

// randint(0, 10) -> 0 .. 10
static int64_t randint(int64_t a, int64_t b)
{
    return ((int64_t)genRandLong(&_rand) % (b - a + 1)) + a;
}


