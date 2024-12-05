#include "uart.h"
#include "lfb.h"
#include <stdio.h>
#include "../doom/doomgeneric.h"

extern volatile unsigned char _binary_doom1_wad_start;
extern volatile unsigned char _binary_doom1_wad_end;

void main() {
    uart_init();
    lfb_init();

    lfb_showpicture();

    // register doom1.wad as file
    FILE* fp = fopen("doom1.wad", "w");
    fp->base = (char*) &_binary_doom1_wad_start;
    fp->ptr = (char*) &_binary_doom1_wad_start;
    fp->bufsiz = &_binary_doom1_wad_end - &_binary_doom1_wad_start;
    fp->count = &_binary_doom1_wad_end - &_binary_doom1_wad_start;

    char* tmp[3] = {"doom", "-iwad", "doom1.wad"};
    doomgeneric_Create(3, tmp);

    while (1) {
        doomgeneric_Tick();
    }

    // // echo everything back
    // while (1) {
    //     uart_send(uart_getc());
    // }
}
