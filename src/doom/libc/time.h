#ifndef SYCL_DOOM_LIBC_TIME_H
#define SYCL_DOOM_LIBC_TIME_H

typedef long time_t;
typedef long clock_t;

#define CLOCKS_PER_SEC 1000000L

clock_t clock(void);

#endif
