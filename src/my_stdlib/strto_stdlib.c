#include "strto_stdlib.h"
#include "my_stdlib.h"
#include <limits.h>

int my_isspace(int c)
{
    return c==' ' || c=='\f' || c=='\n' || c=='\r'|| c=='\t' || c=='\v';
}

size_t ctrl(const char *nptr, int *base, int *sign)
{
    size_t i;
    for(i = 0; nptr[i]!='\0' && my_isspace(nptr[i]); i++);

    *sign = 1;
    if(nptr[i]=='-')
    {
        *sign = -1;
        i++;
    }
    else if(nptr[i]=='+')
        i++;

    if(*base == 0 || *base == 16)
    {
        if(nptr[i]=='0' && (nptr[i+1]=='x' || nptr[i+1]=='X'))
        {
            i+=2;
            *base = 16;
        }
        else if(*base==0)
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
    int sign = 1;
    size_t i = ctrl(nptr, &real_base, &sign);

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
        else if(val>'0' && val<'9')
            val-='0';
        else
            stop = 1;

        if(stop || val>=base)
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
    if(nptr!=NULL)
    {
        if(i==verif)
            *endptr=(char *)nptr;
        else
            *endptr=(char *)nptr+i;
    }

    return sign*res;
}

long long my_strtoll(const char *nptr, char **endptr, int base)
{
    int real_base = base;
    int sign = 1;
    size_t i = ctrl(nptr, &real_base, &sign);

    int stop = 0;
    long long res = 0;
    size_t verif = i;
    for(; nptr[i]!='\0' && !stop; res*=base, i++)
    {
        long val = *(nptr+i);
        if(val>='0' && val<='9')
            val-='0';
        else if(val>='a' && val<='z')
            val-='a'+10;
        else if(val>'A' && val<='Z')
            val-='A'+10;
        else
            stop = 1;

        if(stop || val>=base)
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
    if(nptr!=NULL)
    {
        if(i==verif)
            *endptr=(char *)nptr;
        else
            *endptr=(char *)nptr+i;
    }

    return sign*res;
}

/*
int find_nan(const char *nptr)
{
    char nan[3];
    if(nptr[0]=='n')
        nan = "an";
    else
        nan = "AN";

    size_t i;
    for(i = 0; i<3 && nptr[i]!='\0'; i++)
    {
        if(nptr[i]!=nan[i])
            return 0;
    }

    return i==3;
}

int find_nan(const char *nptr)
{
    char inf[3];
    int lower = nptr[0]=='i';
    if(lower)
        nan = "nf";
    else
        nan = "NF";
    size_t i;
    for(i = 0; i<3 && nptr[i]!='\0'; i++)
    {
        if(nptr[i]!=inf[i])
            return 0;
    }

    if(i==3)
    {
        char inity[6];
        if(lower)
            inity = "inity";
        else
            inity = "INITY";
        for(; i<8 && nptr[i]!='\0' && nptr[i]==inity[i-3]; i++);

        if(i==8)
            return 8;
    }
    else
        return 0;
    if(i==3)
        return 3;
}

double my_strtod(const char *nptr, char **endptr)
{
    int base = 0;
    int sign = 1;
    size_t i = ctrl(nptr, &real_base, &sign);
    double res = 0;

    int is_inf = find_inf(nptr+i)
    if(is_inf)
    {
        i+=is_inf;
        if(sign>0)
            res = POS_INF;
        else
            res = NEG_INF;
    }
    else if(find_nan(&nptr+i))
    {
        i+=3;
        res = NAN;
    }
    else
    {
        int stop = 0;
        for(; nptr[i]!='\0' && !stop; i++)
        {
            int val = nptr[i];
        }
    }

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
*/
