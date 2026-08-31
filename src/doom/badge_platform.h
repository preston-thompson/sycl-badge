#ifndef SYCL_DOOM_BADGE_PLATFORM_H
#define SYCL_DOOM_BADGE_PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t sycl_doom_micros(void);
uint32_t sycl_doom_buttons(void);
void sycl_doom_present(const uint16_t *buffer, uint32_t width, uint32_t height);

#ifdef __cplusplus
}
#endif

#endif
