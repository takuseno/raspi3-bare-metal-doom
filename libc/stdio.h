#pragma once

extern void printf(char *fmt, ...);
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
