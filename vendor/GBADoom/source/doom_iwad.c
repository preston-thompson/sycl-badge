#include "doom_iwad.h"
#include <stdint.h>

extern const unsigned char doom_iwad_start[];
extern const unsigned char doom_iwad_end[];
extern const unsigned int doom_iwad_size;

const unsigned char *const doom_iwad = doom_iwad_start;
const unsigned int doom_iwad_len = (unsigned int)(uintptr_t)&doom_iwad_size;
