#include "string.h"
#include "stdlib.h"

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

int strcmp(const char *s1, const char *s2) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    return strncmp(s1, s2, s1_len > s2_len ? s1_len : s2_len);
}

int strncmp(const char *s1, const char *s2, size_t num) {
    for (int i = 0; i < num; ++i) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        } else {
            ++s1;
            ++s2;
        }
    }
    return 0;
}

char* strncpy(char *dest, const char* src, size_t num) {
    char *ret = dest;
    for (int i = 0; i < num; ++i) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return ret;
}

char* strcpy(char *dest, const char* src) {
    return strncpy(dest, src, strlen(src));
}

char* strstr(const char *str1, const char *str2) {
    int str1_len = strlen(str1);
    for (int i = 0; i < str1_len; ++i) {
        for (int j = 1; j <= str1_len - i; ++j) {
            if (strncmp(str1 + i, str2, j) == 0) {
                return (char*) str1 + i;
            }
        }
    }
    return NULL;
}

char *strdup(const char *s) {
    char* new_s = (char*) malloc(strlen(s) + 1);
    strcpy(new_s, s);
    return new_s;
}
