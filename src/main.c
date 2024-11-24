#include "uart.h"
#include "lfb.h"
#include <stdlib.h>
#include <string.h>

extern volatile unsigned char _binary_data_txt_start;

void main() {
    uart_init();
    lfb_init();

    lfb_showpicture();

    char* ptr = (char*)(&_binary_data_txt_start);
    uart_puts(ptr);

    char* c = (char*) malloc(100);
    c[0] = 'H';
    c[1] = 'e';
    c[2] = 'l';
    c[3] = 'l';
    c[4] = 'o';
    c[5] = '\0';
    uart_puts(c);
    printf("address %x\n", c);

    char* c2 = (char*) malloc(100);
    printf("memcmp %d\n", memcmp(c, c2, 5));
    memcpy(c2, c, 5);
    printf("memcmp %d\n", memcmp(c, c2, 5));
    memset(c2, 'a', 5);
    c2[5] = '\0';
    uart_puts(c2);


    // echo everything back
    while (1) {
        uart_send(uart_getc());
    }
}
