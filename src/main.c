#include "uart.h"
#include "rand.h"

void main() {
    uart_init();
    rand_init();

    uart_puts("Here goes a random number: ");
    uart_hex(rand(0,4294967295));
    uart_puts("\n");

    // echo everything back
    while (1) {
        uart_send(uart_getc());
    }
}
