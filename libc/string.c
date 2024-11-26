#include "string.h"

void* memcpy(void *dest, const void *src, size_t count) {
    for (int i = 0; i < count; ++i) {
        *((char*) src + i) = *((char*) dest + i);
    }
    return dest;
}

void* memmove(void *dest, const void *src, size_t n) {
    return memcpy(dest, src, n);
}

int memcmp(const void *s1, const void *s2, size_t n) {
    for (int i = 0; i < n; ++i) {
        char c1 = *((char*) s1 + i);
        char c2 = *((char*) s2 + i);
        if (c1 != c2) {
            return c1 - c2;
        }
    }
    return 0;
}

void* memset(void *s, int c, size_t n) {
    for (int i = 0; i < n; ++i) {
        *((char*) s + i) = c;
    }
    return s;
}

int strlen(const char* s) {
    int count = 0;
    while (*s++) ++count;
    return count;
}

char *strchr(const char* str, int c) {
    char* ptr = (char*) str;
    while (*ptr) {
        if (*ptr == c) {
            return ptr;
        }
    }
    return NULL;
}

char *strrchr(const char* str, int c) {
    char* ptr = (char*) str;
    // move to end
    while (*ptr) ++ptr;
    // search backwards
    while (ptr <= str) {
        if (*ptr == c) {
            return ptr;
        }
        --ptr;
    }
    return NULL;
}

int strncasecmp(const char *s1, const char *s2, size_t count) {
    for (int i = 0; i < count; ++i) {
        char c1 = *(s1 + i);
        char c2 = *(s2 + i);
        if (c1 == '\0' && c2 != '\0') return -1;
        else if (c1 != '\0' && c2 == '\0') return 1;
        else if (c1 == '\0' && c2 == '\0') return 0;
        else {
            // convert to lower case
            if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
            if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
            if (c1 != c2) return c1 - c2;
        }
    }
    return 0;
}

int strcasecmp(const char *s1, const char *s2) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    int max_len = s1_len > s2_len ? s1_len : s2_len;
    return strncasecmp(s1, s2, max_len);
}
