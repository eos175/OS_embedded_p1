#pragma once

#include <video.h>


// TODO(eos75) posible borrador


typedef struct
{
    int width, height;
    const color_t *data;
} ImageBMP;



static inline rect_t ScaleBMP(void *dst, 
        const void *src, 
        const rect_t rect, int scale)
{
    rect_t r;

    return r;
}


