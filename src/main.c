#include "uart.h"
#include "lfb.h"

extern volatile unsigned char _binary_data_txt_start;

void main() {
    uart_init();
    lfb_init();

    lfb_showpicture();

    char* ptr = (char*)(&_binary_data_txt_start);
    uart_puts(ptr);

    // echo everything back
    while (1) {
        uart_send(uart_getc());
    }
}
