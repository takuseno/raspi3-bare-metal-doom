#include <stdio.h>

#include "m_argv.h"

#include "doomkeys.h"
#include "doomgeneric.h"

// defined in src/delays.c
extern void wait_msec(unsigned int n);
extern unsigned long get_system_timer();
// defined in src/lfb.c
extern void lfb_draw(unsigned int pic_width, unsigned int pic_height, unsigned char *data);
// defined in src/uart.c
extern char uart_getc_no_block();

pixel_t* DG_ScreenBuffer = NULL;

void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create(int argc, char **argv)
{
	// save arguments
    myargc = argc;
    myargv = argv;

	M_FindResponseFile();

	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);

	DG_Init();

	D_DoomMain ();
}

void DG_Init() {
    // do nothing
}

void DG_DrawFrame() {
    lfb_draw(DOOMGENERIC_RESX, DOOMGENERIC_RESY, DG_ScreenBuffer);
}

void DG_SleepMs(uint32_t ms) {
    wait_msec(ms * 1000);
}

uint32_t DG_GetTicksMs() {
    return get_system_timer() / 1000;
}

int DG_GetKey(int* pressed, unsigned char* key) {
    static char prev_c = 0;
    static int count = 0;
    char c = uart_getc_no_block();
    switch (c) {
        case '\n':
            c = KEY_ENTER;
            break;
        case 'a':
            c = KEY_LEFTARROW;
            break;
        case 'd':
            c = KEY_RIGHTARROW;
            break;
        case 's':
            c = KEY_DOWNARROW;
            break;
        case 'w':
            c = KEY_UPARROW;
            break;
        case 'f':
            c = KEY_FIRE;
            break;
        case 'u':
            c = KEY_USE;
            break;
        case 'o':
            c = KEY_ESCAPE;
            break;
        default:
            c = 0;
    }
    if (c > 0 && count <= 0) {
        *key = c;
        prev_c = c;
        *pressed = 1;
        count = 10;
        return 1;
    } else if (prev_c > 0 && count-- <= 0) {
        *pressed = 0;
        *key = prev_c;
        prev_c = 0;
        return 1;
    } else {
        return 0;
    }
}

void DG_SetWindowTitle(const char * title) {
    // do nothing
}
