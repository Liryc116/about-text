#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>

#include "../src/word_generator/sequence.h"
#include "../src/utils/matrix.h"

Test(get_seq, print)
{
    struct matrix *m = get_sequence("lexicons/listefr.txt");

    for(size_t i = 0; i<27; i++)
    {
        double sum = matrix_row_sum(m,i);

        //takes approximation in count
        cr_assert(sum>=0.9999);
        cr_assert(sum<=1.0001);
    }

    matrix_free(m);
}
