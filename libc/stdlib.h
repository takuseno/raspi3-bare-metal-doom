#pragma once
#include "ctype.h"

void* malloc(size_t size);
void* calloc(size_t n, size_t size);
void* realloc(void *ptr, size_t size);
void free(void* ptr);

void exit(int status);

int atoi(const char *nptr);
float atof(const char *nptr);
int abs(int num);
float fabs(float num);
