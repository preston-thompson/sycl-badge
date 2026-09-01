#include <stdint.h>
#include <string.h>

#include "doomdef.h"
#include "doomtype.h"
#include "i_system_e32.h"
#include "badge_platform.h"

static byte indexed_buffer[SCREENWIDTH * SCREENHEIGHT];
static uint16_t rgb565_buffer[SCREENWIDTH * SCREENHEIGHT];

unsigned short *I_GetBackBuffer(void)
{
    return (unsigned short *)indexed_buffer;
}

unsigned short *I_GetFrontBuffer(void)
{
    return (unsigned short *)indexed_buffer;
}

void I_SetPallete_e32(const byte *pallete)
{
    (void)pallete;
}

void I_FinishUpdate_e32(const byte *srcBuffer, const byte *pallete, const unsigned int width, const unsigned int height)
{

    if (srcBuffer && pallete) {
        unsigned int pixels = width * height;
        if (pixels > SCREENWIDTH * SCREENHEIGHT) {
            pixels = SCREENWIDTH * SCREENHEIGHT;
        }
        for (unsigned int i = 0; i < pixels; i++) {
            const byte *rgb = &pallete[srcBuffer[i] * 3];
            rgb565_buffer[i] = (uint16_t)(((rgb[2] & 0xf8) << 8) | ((rgb[1] & 0xfc) << 3) | (rgb[0] >> 3));
        }
    }
    sycl_doom_present(rgb565_buffer);
}
