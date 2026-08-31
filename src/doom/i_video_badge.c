#include <stdint.h>
#include <string.h>

#include "doomdef.h"
#include "doomtype.h"
#include "i_system_e32.h"
#include "badge_platform.h"

static uint16_t backbuffer[SCREENWIDTH * SCREENHEIGHT];

unsigned short *I_GetBackBuffer(void)
{
    return backbuffer;
}

unsigned short *I_GetFrontBuffer(void)
{
    return backbuffer;
}

void I_SetPallete_e32(const byte *pallete)
{
    (void)pallete;
}

void I_FinishUpdate_e32(const byte *srcBuffer, const byte *pallete, const unsigned int width, const unsigned int height)
{
    (void)srcBuffer;
    (void)pallete;
    sycl_doom_present(backbuffer, width, height);
}
