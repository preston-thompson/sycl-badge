#ifndef SYCL_DOOM_BADGE_PLATFORM_H
#define SYCL_DOOM_BADGE_PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t sycl_doom_micros(void);
uint32_t sycl_doom_buttons(void);
void sycl_doom_present_rgb565(const uint16_t *buffer, uint32_t width, uint32_t height);
void sycl_doom_error(const char *message);
void sycl_doom_status(const char *message);

#ifdef __cplusplus
}
#endif

#endif
