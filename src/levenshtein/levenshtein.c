#include "levenshtein.h"

#include <string.h>

size_t my_min(size_t a, size_t b)
{
    if(a<b)
        return a;
    return b;
}

size_t my_max(size_t a, size_t b)
{
    if(a>b)
        return a;
    return b;
}

size_t levenshtein_dist(char *a, char *b)
{
    if(a[0]=='\0' || b[0]=='\0')
        return my_max(strlen(a), strlen(b));
    else if (a[0]==b[0])
        return levenshtein_dist(a+1, b+1);
    else
        return 1+ my_min(levenshtein_dist(a+1, b),
                    my_min(levenshtein_dist(a, b+1),
                        levenshtein_dist(a+1, b+1)));
}
