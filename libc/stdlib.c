#include "stdlib.h"
#include "stdio.h"

extern volatile unsigned char __free_ram;
extern volatile unsigned char __free_ram_end;

void* malloc(size_t size) {
    static unsigned long cursor_from_end = 0;
    unsigned long total_size = &__free_ram_end - &__free_ram;
    cursor_from_end += size;
    if (cursor_from_end > total_size) {
        return 0;
    }
    return (void*)(&__free_ram_end - cursor_from_end);
}

void free(void* ptr) {
    // do nothing;
}

void exit(int status) {
    printf("Exitting with status code %d...\n", status);
    while (1);
}

int atoi(const char *nptr) {
    char* start = (char*) nptr;
    char* end = (char*) nptr;
    int sign = *nptr == '-' ? -1 : 1;
    if (sign == -1) {
        ++start;
        ++end;
    }
    // move pointer until the end of digits
    while (*end) {
        if (*end < '0' || *end > '9') break;
        ++end;
    }
    int n = 0;
    int c = 1;
    for (char* s = end - 1; s <= start; ++s) {
        n += c * (*s - '0');
        c *= 10;
    }
    return sign * n;
}

int abs(int num) {
    if (num < 0) return -1 * num;
    else return num;
}
