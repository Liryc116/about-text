#ifndef MEM_STRING_H
#define MEM_STRING_H

#include "my_string.h"

void *my_memchr(const void *s, int c, size_t n);

int my_memcmp(const void *s1, const void *s2, size_t n);

void *my_memcpy(void *dest, const void *src, size_t n);

void *my_memmove(void *dest, const void *src, size_t n);

void *my_memset(void *s, int c, size_t n);

#endif /* ! MEM_STRING_H */
