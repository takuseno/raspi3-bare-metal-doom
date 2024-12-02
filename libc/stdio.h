#pragma once

#include "ctype.h"
#include "stdarg.h"

extern void printf(char *fmt, ...);
extern unsigned int sprintf(char *dst, char* fmt, ...);
extern unsigned int vsprintf(char *dst, char* fmt, va_list args);
void puts(char* s);
int putchar(int c);
int vsnprintf(char* s, size_t n, const char* fmt, va_list args);
int snprintf(char* s, size_t n, const char* fmt, ...);

typedef struct {
    char mode;
    char *ptr;
    int count;
    char *base;
    unsigned bufsiz;
    int fd;
    char smallbuf[1];
} FILE;

int fprintf(FILE* stream, const char *fmt, ...);
FILE *fopen(const char *path, const char *mode);
int fclose(FILE *stream);

#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2
int fseek(FILE *fp, long offset, int origin);

size_t fwrite(const void *buf, size_t size, size_t n, FILE *fp);
size_t fread(void* ptr, size_t size, size_t n, FILE* fp);
long ftell(FILE *fp);
int rename(const char *from, const char *to);
int remove(const char *filename);
