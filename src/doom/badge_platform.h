#ifndef SYCL_DOOM_BADGE_PLATFORM_H
#define SYCL_DOOM_BADGE_PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t sycl_doom_tics(void);
uint32_t sycl_doom_buttons(void);
void sycl_doom_present(const uint16_t *buffer);
void sycl_doom_status(const char *message);

#ifdef __cplusplus
}
#endif

#endif
