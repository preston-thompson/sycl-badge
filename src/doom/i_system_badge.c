#include <stdarg.h>
#include <stdio.h>

#include "doomdef.h"
#include "doomtype.h"
#include "d_event.h"
#include "d_main.h"
#include "i_system_e32.h"
#include "badge_platform.h"

enum {
    BTN_START = 1u << 0,
    BTN_SELECT = 1u << 1,
    BTN_A = 1u << 2,
    BTN_B = 1u << 3,
    BTN_UP = 1u << 4,
    BTN_DOWN = 1u << 5,
    BTN_LEFT = 1u << 6,
    BTN_RIGHT = 1u << 7,
    BTN_CLICK = 1u << 8,
};

static uint32_t last_buttons;

static void post_button_event(uint32_t changed, uint32_t current, uint32_t mask, int key)
{
    if ((changed & mask) == 0) {
        return;
    }

    event_t ev;
    ev.type = (current & mask) ? ev_keydown : ev_keyup;
    ev.data1 = key;
    ev.data2 = 0;
    ev.data3 = 0;
    D_PostEvent(&ev);
}

void I_InitScreen_e32(void) {}
void I_CreateBackBuffer_e32(void) {}
void I_StartWServEvents_e32(void) {}
void I_ClearWindow_e32(void) {}
void I_Quit_e32(void) {}

int I_GetVideoWidth_e32(void) { return SCREENWIDTH; }
int I_GetVideoHeight_e32(void) { return SCREENHEIGHT; }

int I_GetTime_e32(void)
{
    return (int)(sycl_doom_micros() / (1000000u / TICRATE));
}

void I_ProcessKeyEvents(void)
{
    uint32_t current = sycl_doom_buttons();
    uint32_t changed = current ^ last_buttons;
    last_buttons = current;

    post_button_event(changed, current, BTN_UP, KEYD_UP);
    post_button_event(changed, current, BTN_DOWN, KEYD_DOWN);
    post_button_event(changed, current, BTN_LEFT, KEYD_LEFT);
    post_button_event(changed, current, BTN_RIGHT, KEYD_RIGHT);
    post_button_event(changed, current, BTN_START, KEYD_START);
    post_button_event(changed, current, BTN_SELECT, KEYD_SELECT);
    post_button_event(changed, current, BTN_A, KEYD_A);
    post_button_event(changed, current, BTN_B, KEYD_B);
    post_button_event(changed, current, BTN_CLICK, KEYD_R);
}

void I_Error(const char *error, ...)
{
    char buffer[128];
    va_list args;
    va_start(args, error);
    vsnprintf(buffer, sizeof(buffer), error, args);
    va_end(args);
    sycl_doom_error(buffer);
    while (1) {}
}
