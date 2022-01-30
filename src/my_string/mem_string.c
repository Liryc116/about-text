#include "mem_string.h"

void *my_memchr(const void *s, int c, size_t n)
{
    void *ret = NULL;
    for(size_t i = 0; i<n; i++)
    {
        if(*((unsigned char *)s+n)==c)
            ret = (char *)(s+n);
    }

    return ret;
}

int my_memcmp(const void *s1, const void *s2, size_t n)
{
    if(n==0)
        return 0;

    size_t i = 0;
    for(; i<n && *(char *)s1+n==*(char *)s2+n; i++);

    if(i==n)
        return 0;

    unsigned char c1 = *(char *)(s1+n);
    unsigned char c2 = *(char *)(s2+n);
    return c1-c2;
}

void *my_memcpy(void *dest, const void *src, size_t n)
{
    for(size_t i = 0; i<n; i++)
        *(char *)(dest+i) = *(char *)(src+i);
    return dest;
}

void *memrcpy(void *dest, const void *src, size_t n)
{
    for(size_t i = n; i>0; i--)
        *(char *)(dest+i-1) = *(char *)(src+i-1);
    return dest;
}

void *my_memmove(void *dest, const void *src, size_t n)
{
    if(src>dest)
        return my_memcpy(dest, src, n);
    else
        return memrcpy(dest, src, n);
}

void *my_memset(void *s, int c, size_t n)
{
    for(size_t i = 0; i<n; i++)
        *(char *)(s+i)=c;
    return s;
}
