#include "strto_stdlib.h"
#include "my_stdlib.h"

int my_isspace(int c)
{
    return c==' ' || c=='\f' || c=='\n' || c=='\r'|| c=='\t' || c=='\v';
}

size_t ctrl(const char *nptr, int *base)
{
    size_t i;
    for(i = 0; nptr[i]!='\0' && isspace(nptr[i]; i++));

    int sign = 1;
    if(nptr[i]=='-')
    {
        sign = -1;
        i++;
    }
    else if(nptr[i]=='+')
        i++;

    if(base == 0 || base == 16)
    {
        if(nptr[i]=='0' && (nptr[i+1]=='x' || nptr[i+1]=='X'))
        {
            i+=2;
            *base = 16;
        }
        else if(base==0)
        {
            if(nptr[i]=='0')
            {
                *base = 8;
                i+=1;
            }
            else
                *base = 10;
        }
    }

    return i;
}

long my_strtol(const char *nptr, char **endptr, int base)
{
    int real_base = base;
    size_t i = ctrl(nptr, &real_base);

    int stop = 0;
    long res = 0;
    size_t verif = i;
    for(; nptr[i]!='\0' && !stop; res*=base, i++)
    {
        long val = *(nptr+i);
        if(val>='a' && val<='z')
            val-='a'+10;
        else if(val>'A' && val<='Z')
            val-='A'+10;

        if(val>=base)
            stop = 1;
        else if( val > LONG_MAX - res || res+val>LONG_MAX/base )
        {
            stop = 1;
            res = LONG_MAX;
        }
        else if( val < LONG_MIN - res || res+val<LONG_MIN/base)
        {
            stop = 1;
            res = LONG_MIN;
        }
        else
            res+=val;
    }
    if(i==verif)
        *endptr=nptr;
    else
        *endptr=nptr+i;

    return sign*res;
}

long long my_strtoll(const char *nptr, char **endptr, int base)
{
    int real_base = base;
    size_t i = ctrl(nptr, &real_base);

    int stop = 0;
    long long res = 0;
    size_t verif = i;
    for(; nptr[i]!='\0' && !stop; res*=base, i++)
    {
        long val = *(nptr+i);
        if(val>='a' && val<='z')
            val-='a'+10;
        else if(val>'A' && val<='Z')
            val-='A'+10;

        if(val>=base)
            stop = 1;
        else if( val > LLONG_MAX - res || res+val>LLONG_MAX/base )
        {
            stop = 1;
            res = LLONG_MAX;
        }
        else if( val < LLONG_MIN - res || res+val<LLONG_MIN/base)
        {
            stop = 1;
            res = LLONG_MIN;
        }
        else
            res+=val;
    }
    if(i==verif)
        *endptr=nptr;
    else
        *endptr=nptr+i;

    return sign*res;
}

double my_strtod(const char *nptr, char **endptr)
{
    double res = 0;
    return res;
}

float my_strtof(const char *nptr, char **endptr)
{
    float res = 0;
    return res;
}

long double my_strtold(const char *nptr, char **endptr)
{
    long double res = 0;

    return res;
}
