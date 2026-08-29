#include "d_main.h"
#include "doomstat.h"
#include "global_data.h"
#include "i_main.h"
#include "i_sound.h"
#include "i_video.h"
#include "z_zone.h"
#include "badge_platform.h"

void I_Init(void)
{
    I_InitSound();
}

int sycl_doom_main(void)
{
    sycl_doom_status("preinit graphics");
    I_PreInitGraphics();
    sycl_doom_status("init sound");
    I_Init();
    sycl_doom_status("zone init");
    Z_Init();
    sycl_doom_status("globals init");
    InitGlobals();
    sycl_doom_status("doom main");
    D_DoomMain();
    return 0;
}
