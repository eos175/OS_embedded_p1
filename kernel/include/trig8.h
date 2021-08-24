#pragma once

#include <stdint.h>


/*

https://github.com/FastLED/FastLED/blob/master/src/lib8tion/trig8.h

*/


typedef uint_fast8_t 	uint8;
typedef int_fast8_t 	int8;

typedef int_fast16_t 	uint16;
typedef uint_fast16_t 	int16;


static const uint8 PI8 = 127;

static const uint16 PI16 = 32768;


static inline uint8_t sin8(uint8 theta) 
{
    static const uint8 bM16Interleave[] = {0, 49, 49, 41, 90, 27, 117, 10};

    uint8 offset = theta;
	if ((theta & 0x40) != 0) {
		offset = 255 - offset;
	}
	offset &= 0x3F; // 0..63

	uint8 secoffset = offset & 0x0F; // 0..15
	if ((theta & 0x40) != 0) {
		secoffset++;
	}

	uint8 section = offset >> 4; // 0..3
	uint8 s2 = section * 2;

	uint8 p, b, m16;

    p = s2;
	b = bM16Interleave[p];
	p++;
	m16 = bM16Interleave[p];

    int16 mx, y;
	mx = (m16 * secoffset) >> 4;

	y = mx + b;
	if ((theta & 0x80) != 0) {
		y = -y;
	}

	y += 128;
	return y;
}

static inline uint8_t cos8(uint8 theta) {
    return sin8(theta + 64);
}



static inline int16_t sin16(uint16 theta) {

    static const uint16 base[] = {0, 6393, 12539, 18204, 23170, 27245, 30273, 32137};
    static const uint8 slope[] = {49, 48, 44, 38, 31, 23, 14, 4};

	uint16 offset = (theta & 0x3FFF) >> 3; // 0..2047

	if ((theta & 0x4000) != 0) {
		offset = 2047 - offset;
	}

	uint16 section, b, m;

	section = offset / 256; // 0..7
	b = base[section];
	m = slope[section];


	uint8 secoffset8 = (uint8)offset / 2;
    
    int16 mx, y;
	mx = m * secoffset8;
	y = mx + b;

	if ((theta & 0x8000) != 0) {
		y = -y;
	}

	return y;
}

static inline int16_t cos16(uint16 theta)  {
	return sin16(theta + 16384);
}



