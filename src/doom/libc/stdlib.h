#ifndef SYCL_DOOM_LIBC_STDLIB_H
#define SYCL_DOOM_LIBC_STDLIB_H

#include <stddef.h>

void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void free(void *ptr);
void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void exit(int status);
int atoi(const char *s);
int abs(int x);
char *itoa(int value, char *str, int base);

#endif
