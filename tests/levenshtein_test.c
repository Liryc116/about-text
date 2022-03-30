#include <stdlib.h>
#include <criterion/criterion.h>

#include "../src/levenshtein/levenshtein.h"

Test(lev_dist, dist_5)
{
    cr_assert(levenshtein_dist("chiens", "niche")==5);
}

Test(lev_dist, dist_0)
{
    cr_assert(levenshtein_dist("chiens", "chiens")==0);
}

Test(lev_dist, dist_1)
{
    cr_assert(levenshtein_dist("chiens", "chien")==1);
    cr_assert(levenshtein_dist("chien", "chiens")==1);
}
