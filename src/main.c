#include "uart.h"
#include "lfb.h"

extern volatile unsigned char _binary_data_txt_start;

void main() {
    uart_init();
    lfb_init();

    lfb_showpicture();

    char* ptr = (char*)(&_binary_data_txt_start);
    uart_puts(ptr);

    printf( "Hello %s!\n"
            "This is character '%c', a hex number: %x and in decimal: %d\n"
            "Padding test: '%8x', '%8d'\n",
            "World", 'A', 32767, 32767, 0x7FFF, -123);

    // echo everything back
    while (1) {
        uart_send(uart_getc());
    }
}
