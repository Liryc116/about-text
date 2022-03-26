#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <time.h>

#include "../src/word_generator/sequence.h"
#include "../src/word_generator/generator.h"
#include "../src/utils/matrix.h"

Test(word_exact_gen, gen_5_5)
{
    struct matrix *m = get_sequence("lexicons/listefr.txt");

    srand(time(0));
    for(size_t i = 0; i<5; i++)
    {
        char *word = gen_exact_word(m, 5);
        printf("%s\n", word);
        free(word);
    }

    matrix_free(m);
}

Test(word_exact_gen, gen_5_7)
{
    struct matrix *m = get_sequence("lexicons/listefr.txt");

    srand(time(0));
    for(size_t i = 0; i<5; i++)
    {
        char *word = gen_exact_word(m, 7);
        printf("%s\n", word);
        free(word);
    }

    matrix_free(m);
}

Test(word_gen, gen_5_5)
{
    struct matrix *m = get_sequence("lexicons/listefr.txt");
    srand(time(0));

    for(size_t i = 0; i<5; i++)
    {
        char *word = gen_word(m, 5);
        printf("%s\n", word);
        free(word);
    }

    matrix_free(m);
}
