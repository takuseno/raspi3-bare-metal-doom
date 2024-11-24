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
