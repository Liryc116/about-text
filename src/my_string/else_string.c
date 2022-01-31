#include "else_string.h"

size_t my_strlen(const char *str)
{
    size_t i;
    for(i=0; str[i]!='\0'; i++);

    return i;
}

char *my_strstr(const char *haystack, const char *needle)
{
    for(size_t i = 0; haystack[i]!='\0'; i++)
    {
        size_t k;
        for(k = 0; needle[k]!='\0' && haystack[i]==needle[k]; i++, k++);

        if(needle[k]=='\0')
            return (char *)(haystack+i);
    }

    return NULL;
}

size_t my_strspn(const char *s, const char *accept)
{
    size_t i;
    for(i = 0; s[i]!='\0'; i++)
    {
        for(size_t j = 0; accept[j]!='\0'; j++)
        {
            if(s[i]==accept[j])
                return i;
        }
    }

    return i;
}

char *my_strrchr(const char *s, int c)
{
    size_t i;
    size_t a = 0;
    for(i = 0; s[i]!='\0'; i++)
    {
        if(s[i]==c)
            a=i;
    }

    if(c=='\0')
        return (char *)(s+i);
    else if(s[a]!=c)
        return NULL;

    return (char *)(s+a);
}

char *my_strtok(char *str, const char *delim)
{
    static char *s = NULL;

    if(str!=NULL)
        s=str;
    if(*s=='\0')
        return NULL;
    char *ret = s;

    for(; *s!='\0'; s++)
    {
        for(size_t j = 0; delim[j]!='\0'; j++)
        {
            if(*s==delim[j])
            {
                *s='\0';
                if(ret==s)
                    ret++;
                else
                {
                    s++;
                    return ret;
                }
            }
        }
    }

    return ret;
}
