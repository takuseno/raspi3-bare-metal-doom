#include "ctype.h"

int toupper(int c) {
    if (c >= 'a' && c <= 'z') return 'A' + c - 'a';
    else return c;
}

int isspace(int c) {
    if (c == ' ') return 1;
    else return 0;
}
