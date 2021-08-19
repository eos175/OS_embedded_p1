#include <random.h>


static MTRand _rand;

void random_init(uint64_t seed) {
    _rand = seedRand(seed);
}

int64_t randint(int64_t a, int64_t b) {
    return ((int64_t)genRandLong(&_rand) % (b - a + 1)) + a;
}




