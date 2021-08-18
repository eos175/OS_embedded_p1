#pragma once

#include <stddef.h>
#include <stdint.h>


int isdigit(char c);
void strcpy(char *dst, const char *source);
void strcat(char *dst, const char *src);
size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);

void memset(void *buf, uint8_t value, size_t count);
void memset16(void *buf, uint16_t value, size_t count);
void memset32(void *buf, uint32_t value, size_t count);
void memset64(void *buf, uint64_t value, size_t count);

void memcpy(void *dst, const void *src, size_t length);
void memcpy16(void *dst, const void *src, size_t length);
void memcpy32(void *dst, const void *src, size_t length);
void memcpy64(void *dst, const void *src, size_t length);
