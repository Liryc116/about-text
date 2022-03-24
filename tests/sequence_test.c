#include <stdlib.h>
#include <criterion/criterion.h>

#include "../src/word_generator/sequence.h"
#include "../src/utils/matrix.h"

Test(get_seq, print)
{
    struct matrix *m = get_sequence("lexicons/listefr.txt");
    to_probability(m);

    for(size_t i = 0; i<27; i++)
        cr_assert(matrix_row_sum(m, i)-1.0<0.0001);
    //takes approximation in count

    matrix_free(m);
}
