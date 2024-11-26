#include "stdio.h"

void puts(char* s) {
    printf(s);
}

int fprintf(FILE* stream, const char *fmt, ...) {
    __builtin_va_list args;
    __builtin_va_start(args, fmt);
    return vsprintf(stream->ptr, (char*) fmt, args);
}
