#include "string.h"

void* memcpy(void *dest, const void *src, size_t count) {
    for (int i = 0; i < count; ++i) {
        *((char*) src + i) = *((char*) dest + i);
    }
    return dest;
}

void* memmove(void *dest, const void *src, size_t n) {
    return memcpy(dest, src, n);
}

int memcmp(const void *s1, const void *s2, size_t n) {
    for (int i = 0; i < n; ++i) {
        char c1 = *((char*) s1 + i);
        char c2 = *((char*) s2 + i);
        if (c1 != c2) {
            return c1 - c2;
        }
    }
    return 0;
}

void* memset(void *s, int c, size_t n) {
    for (int i = 0; i < n; ++i) {
        *((char*) s + i) = c;
    }
    return s;
}

int strlen(char* s) {
    int count = 0;
    while (*s++) ++count;
    return count;
}
