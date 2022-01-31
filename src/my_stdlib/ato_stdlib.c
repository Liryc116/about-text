#include "ato_stdlib.h"
#include "my_stdlib.h"

int my_atoi(const char *nptr)
{
    int res = 0;
    for(size_t i = 0; nptr[i]!='\0'; res=res*10+*(nptr+i)-'0', i++);

    return res;
}

long my_atol(const char *nptr)
{
    long res = 0;
    for(size_t i = 0; nptr[i]!='\0'; res=res*10+*(nptr+i)-'0', i++);

    return res;
}

long long my_atoll(const char *nptr)
{
    long long res = 0;
    for(size_t i = 0; nptr[i]!='\0'; res=res*10+*(nptr+i)-'0', i++);

    return res;
}
