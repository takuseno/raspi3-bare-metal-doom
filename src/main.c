#include "uart.h"
#include "lfb.h"
#include <stdio.h>
#include "../doom/doomgeneric.h"

extern volatile unsigned char _binary_doom1_wad_start;
extern volatile unsigned char _binary_doom1_wad_end;

void main() {
    uart_init();
    lfb_init();

    // register doom1.wad as file
    FILE* fp = fopen("doom1.wad", "w");
    fp->base = (char*) &_binary_doom1_wad_start;
    fp->ptr = (char*) &_binary_doom1_wad_start;
    fp->bufsiz = &_binary_doom1_wad_end - &_binary_doom1_wad_start;
    fp->count = &_binary_doom1_wad_end - &_binary_doom1_wad_start;

    char *arg0 = "doom";
    char *arg1 = "-iwad";
    char *arg2 = "doom1.wad";
    char* argv[3];
    argv[0] = arg0;
    argv[1] = arg1;
    argv[2] = arg2;
    doomgeneric_Create(3, argv);

    while (1) {
        doomgeneric_Tick();
    }

    // // echo everything back
    // while (1) {
    //     uart_send(uart_getc());
    // }
}
