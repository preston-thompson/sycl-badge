#include "d_main.h"
#include "doomstat.h"
#include "global_data.h"
#include "i_main.h"
#include "i_sound.h"
#include "i_video.h"
#include "z_zone.h"

void I_Init(void)
{
    I_InitSound();
}

int sycl_doom_main(void)
{
    I_PreInitGraphics();
    I_Init();
    Z_Init();
    InitGlobals();
    D_DoomMain();
    return 0;
}
