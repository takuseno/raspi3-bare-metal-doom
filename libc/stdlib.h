#pragma once
#include "ctype.h"

void* malloc(size_t size);
void free(void* ptr);

void exit(int status);

int atoi(const char *nptr);
int abs(int num);
