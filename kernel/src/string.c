#include <stddef.h>
#include <stdint.h>
#include <string.h>


int isdigit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return 1;
    }
    return 0;
}

void strcpy(char *dst, const char *source) {
    int i = 0;
    while ((dst[i] = source[i]) != 0)
        i++;
}

void strcat(char *dst, const char *src) {
    while (*dst)
        dst++;
    while ((*dst++ = *src++))
        ;
}

size_t strlen(const char *s) {
    size_t i = 0;

    for (; s[i] != 0; i++)
        ;
    
    return i;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i])
            return 1;
    }

    return 0;
}

