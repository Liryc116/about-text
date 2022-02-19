#include "string_manipulation.h"

#include <string.h>
#include <stdlib.h>

char *strnstr(char *haystack, char *needle, size_t n)
{
    for(size_t i = 0; haystack[i]!='\0' && i<n; i++)
    {
        size_t k;
        for(k = 0; needle[k]!='\0' && haystack[i]==needle[k]; i++, k++);

        if(needle[k]=='\0')
            return (char *)(haystack+i);
    }

    return NULL;
}

char *stracpy(char *src)
{
    char *dest = calloc(strlen(src)+1, sizeof(char));

    for (size_t i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];

    return dest;
}

int is_all_capital(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if(str[i]<'A' || str[i]>'Z')
            return 0;
    }

    return 1;
}
char *skip_ignored(char *str)
{
    size_t i;

    for(i = 0; str[i]==' ' || str[i]=='\t'; i++);

    return str+i;
}
