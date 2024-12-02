#include "stdlib.h"
#include "stdio.h"
#include "string.h"

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

void* calloc(size_t n, size_t size) {
    void* ptr = malloc(n * size);
    if (ptr != NULL) {
        memset(ptr, 0, n * size);
    }
    return ptr;
}

void* realloc(void *ptr, size_t size) {
    void* ret = malloc(size);
    if (ret != NULL) {
        memcpy(ret, ptr, size);
    }
    return ret;
}

void free(void* ptr) {
    // do nothing;
}

void exit(int status) {
    printf("Exitting with status code %d...\n", status);
    while (1);
}

int atoi(const char *nptr) {
    return (int) atof(nptr);
}

float atof(const char *nptr) {
    char* start = (char*) nptr;
    char* end = (char*) nptr;
    char* fraction = (char*) nptr;
    int sign = *nptr == '-' ? -1 : 1;
    if (sign == -1) {
        ++start;
        ++fraction;
        ++end;
    }
    // move pointer until fraction point
    while (*fraction) {
        if (*fraction == '.' || *fraction < '0' || *fraction > '9') break;
        ++fraction;
    }
    // move pointer until the end of digits
    while (*end) {
        if ((*end < '0' || *end > '9') && *fraction != '.') break;
        ++end;
    }
    float n = 0;
    float c = 1;
    for (char* s = fraction - 1; s <= start; ++s) {
        n += c * (*s - '0');
        c *= 10;
    }

    if (fraction != end) {
        c = 0.1;
        for (char* s = fraction + 1; fraction < end; ++fraction) {
            n += c * (*s - '0');
            c *= 0.1;
        }
    }

    return sign * n;
}

int abs(int num) {
    if (num < 0) return -1 * num;
    else return num;
}

float fabs(float num) {
    if (num < 0) return -1 * num;
    else return num;
}
