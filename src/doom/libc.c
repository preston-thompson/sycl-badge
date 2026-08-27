#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int errno;

static unsigned char heap[384 * 1024];
static size_t heap_pos;

void *malloc(size_t size)
{
    size = (size + 7u) & ~7u;
    if (heap_pos + size > sizeof(heap)) {
        return 0;
    }
    void *ptr = &heap[heap_pos];
    heap_pos += size;
    return ptr;
}

void free(void *ptr) { (void)ptr; }

void *calloc(size_t count, size_t size)
{
    size_t total = count * size;
    void *ptr = malloc(total);
    if (ptr) memset(ptr, 0, total);
    return ptr;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--) *d++ = *s++;
    return dest;
}

void *memset(void *dest, int c, size_t n)
{
    unsigned char *d = dest;
    while (n--) *d++ = (unsigned char)c;
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = s1;
    const unsigned char *b = s2;
    while (n--) {
        if (*a != *b) return (int)*a - (int)*b;
        a++;
        b++;
    }
    return 0;
}

void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *p = s;
    while (n--) {
        if (*p == (unsigned char)c) return (void *)p;
        p++;
    }
    return 0;
}

size_t strlen(const char *s)
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

char *strcpy(char *dest, const char *src)
{
    char *d = dest;
    while ((*d++ = *src++)) {}
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    for (; i < n && src[i]; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = 0;
    return dest;
}

char *strcat(char *dest, const char *src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2) { s1++; s2++; }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && *s1 == *s2) { s1++; s2++; n--; }
    return n ? (unsigned char)*s1 - (unsigned char)*s2 : 0;
}

char *strchr(const char *s, int c)
{
    while (*s) {
        if (*s == (char)c) return (char *)s;
        s++;
    }
    return c == 0 ? (char *)s : 0;
}

char *strrchr(const char *s, int c)
{
    const char *last = 0;
    do {
        if (*s == (char)c) last = s;
    } while (*s++);
    return (char *)last;
}

char *strstr(const char *haystack, const char *needle)
{
    size_t nlen = strlen(needle);
    if (nlen == 0) return (char *)haystack;
    for (; *haystack; haystack++) {
        if (strncmp(haystack, needle, nlen) == 0) return (char *)haystack;
    }
    return 0;
}

char *strupr(char *s)
{
    char *p = s;
    while (*p) {
        *p = (char)toupper((unsigned char)*p);
        p++;
    }
    return s;
}

int toupper(int c) { return c >= 'a' && c <= 'z' ? c - ('a' - 'A') : c; }
int tolower(int c) { return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c; }
int isalpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
int isdigit(int c) { return c >= '0' && c <= '9'; }
int isspace(int c) { return c == ' ' || (c >= 9 && c <= 13); }
int abs(int x) { return x < 0 ? -x : x; }

int atoi(const char *s)
{
    int sign = 1;
    int value = 0;
    while (isspace((unsigned char)*s)) s++;
    if (*s == '-') { sign = -1; s++; }
    while (isdigit((unsigned char)*s)) value = value * 10 + (*s++ - '0');
    return sign * value;
}

char *itoa(int value, char *str, int base)
{
    char tmp[34];
    unsigned int v;
    int i = 0;
    int neg = 0;
    char *out = str;

    if (base < 2 || base > 36) {
        str[0] = 0;
        return str;
    }
    if (value < 0 && base == 10) {
        neg = 1;
        v = (unsigned int)-value;
    } else {
        v = (unsigned int)value;
    }
    do {
        unsigned int digit = v % (unsigned int)base;
        tmp[i++] = (char)(digit < 10 ? '0' + digit : 'a' + digit - 10);
        v /= (unsigned int)base;
    } while (v);
    if (neg) *out++ = '-';
    while (i) *out++ = tmp[--i];
    *out = 0;
    return str;
}

void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    unsigned char *data = base;
    size_t i;
    if (size > 64) return;
    for (i = 1; i < nmemb; i++) {
        size_t j = i;
        unsigned char tmp[64];
        memcpy(tmp, data + i * size, size);
        while (j > 0 && compar(data + (j - 1) * size, tmp) > 0) {
            memcpy(data + j * size, data + (j - 1) * size, size);
            j--;
        }
        memcpy(data + j * size, tmp, size);
    }
}

void exit(int status)
{
    (void)status;
    while (1) {}
}

int vsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
    (void)ap;
    size_t i = 0;
    if (size == 0) return 0;
    while (fmt[i] && i + 1 < size) {
        str[i] = fmt[i];
        i++;
    }
    str[i] = 0;
    return (int)i;
}

int vsprintf(char *str, const char *fmt, va_list ap) { return vsnprintf(str, (size_t)-1, fmt, ap); }

int snprintf(char *str, size_t size, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int r = vsnprintf(str, size, fmt, ap);
    va_end(ap);
    return r;
}

int sprintf(char *str, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int r = vsprintf(str, fmt, ap);
    va_end(ap);
    return r;
}

int printf(const char *fmt, ...) { (void)fmt; return 0; }

int close(int fd) { (void)fd; return -1; }
int read(int fd, void *buf, size_t count) { (void)fd; (void)buf; (void)count; return -1; }
long lseek(int fd, long offset, int whence) { (void)fd; (void)offset; (void)whence; return -1; }

double floor(double x) { return (double)((long long)x); }
double ceil(double x) { long long i = (long long)x; return x == (double)i ? x : (double)(i + 1); }
double sqrt(double x) { (void)x; return 0.0; }
double sin(double x) { (void)x; return 0.0; }
double cos(double x) { (void)x; return 1.0; }
clock_t clock(void) { return 0; }
