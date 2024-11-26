#pragma once
#include "ctype.h"

void* memcpy(void *dest, const void *src, size_t count);
void* memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void* memset(void *s, int c, size_t n);
int strlen(const char* s);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
int strncasecmp(const char *s1, const char *s2, size_t count);
int strcasecmp(const char *s1, const char *s2);
