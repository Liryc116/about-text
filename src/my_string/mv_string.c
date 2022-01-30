#include "mv_string.h"

char *my_strcpy(char *dest, const char *src)
{
    size_t i;
    for(i = 0; src[i]!='\0'; i++)
        dest[i]=src[i];

    dest[i] = '\0';

    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for(i = 0; i<n && src[i]!='\0'; i++)
        dest[i]=src[i];

    for(; i<n; i++)
        dest[i]='\0';

    return dest;
}

char *my_strcat(char *dest, const char *src)
{
    size_t i;
    for(i=0; dest[i]!='\0'; i++);
    for(size_t k = 0; src[k]!='\0'; dest[i]=src[k], k++, i++);

    dest[i] = '\0';

    return dest;
}

char *my_strncat(char *dest, const char *src, size_t n)
{
    size_t i;
    for(i=0; dest[i]!='\0'; i++);
    for(size_t k = 0; k<n && src[k]!='\0'; dest[i]=src[k], k++, i++);

    dest[i] = '\0';

    return dest;
}
