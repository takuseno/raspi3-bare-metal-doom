#include <stdio.h>

#include "m_argv.h"

#include "doomgeneric.h"

// defined in src/delays.c
extern void wait_msec(unsigned int n);
extern unsigned long get_system_timer();
// defined in src/lfb.c
extern void lfb_draw(unsigned int pic_width, unsigned int pic_height, unsigned char *data);

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
    wait_msec(ms);
}

uint32_t DG_GetTicksMs() {
    return get_system_timer();
}

int DG_GetKey(int* pressed, unsigned char* key) {
    return 0;
}

void DG_SetWindowTitle(const char * title) {
    // do nothing
}
