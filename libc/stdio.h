#pragma once

extern void printf(char *fmt, ...);
extern unsigned int sprintf(char *dst, char* fmt, ...);
extern unsigned int vsprintf(char *dst, char* fmt, __builtin_va_list args);
void puts(char* s);

typedef struct {
    char mode;
    char *ptr;
    int rcount;
    int wcount;
    char *base;
    unsigned bufsiz;
    int fd;
    char smallbuf[1];
} FILE;

FILE* stderr;
FILE* stdout;

int fprintf(FILE* stream, const char *fmt, ...);
