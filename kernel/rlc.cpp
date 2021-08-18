#include "rlc.h"
#include "rlc.hpp"



int RLE_Decode(void *dst1, const void *src1, size_t size)
{
    return rle_decode<uint32_t>(dst1, src1, size);
}


