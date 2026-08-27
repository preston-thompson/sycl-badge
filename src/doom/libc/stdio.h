#ifndef SYCL_DOOM_LIBC_STDIO_H
#define SYCL_DOOM_LIBC_STDIO_H

#include <stddef.h>
#include <stdarg.h>

#define EOF (-1)

int printf(const char *fmt, ...);
int sprintf(char *str, const char *fmt, ...);
int snprintf(char *str, size_t size, const char *fmt, ...);
int vsprintf(char *str, const char *fmt, va_list ap);
int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);

#endif
