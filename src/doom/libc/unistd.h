#ifndef SYCL_DOOM_LIBC_UNISTD_H
#define SYCL_DOOM_LIBC_UNISTD_H

#include <stddef.h>

int close(int fd);
int read(int fd, void *buf, size_t count);
long lseek(int fd, long offset, int whence);

#endif
