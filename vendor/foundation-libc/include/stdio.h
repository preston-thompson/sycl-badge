#ifndef _FOUNDATION_LIBC_STDIO_H_
#define _FOUNDATION_LIBC_STDIO_H_

#include <stdarg.h>
#include <stddef.h>

int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int printf(const char *format, ...);

#endif
