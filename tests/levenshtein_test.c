#include <stdlib.h>
#include <criterion/criterion.h>
#include <time.h>

#include "../src/levenshtein/levenshtein.h"

Test(lev_dist, dist_5)
{
    cr_assert(levenshtein_dist("chiens", "niche")==5);
}
