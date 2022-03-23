#include <stdlib.h>
#include <criterion/criterion.h>
#include "../src/wordle/wordle.h"

Test(evaluate, a_a)
{
    int *res = evaluate_answer("a", "a");

    cr_assert(res[0]==GREEN);

    free(res);
}

Test(evaluate, a_b)
{
    int *res = evaluate_answer("a", "b");

    cr_assert(res[0]==GRAY);

    free(res);
}

Test(evaluate, ab_bd)
{
    int *res = evaluate_answer("ab", "bd");
    int expect[2] = {YELLOW, GRAY};

    for(size_t i = 0; i<2; i++)
        cr_assert(res[i]==expect[i]);

    free(res);
}

Test(evaluate, abc_adb)
{
    int *res = evaluate_answer("abc", "adb");
    int expect[3] = {GREEN, GRAY, YELLOW};

    for(size_t i = 0; i<3; i++)
        cr_assert(res[i]==expect[i]);

    free(res);
}

Test(init_word_list, right_len_3)
{
    struct vector *v = init_word_list("lexicons/lex_first.txt", 3);
    cr_assert(v->size==9);
    vector_free(v, &free);
}

Test(init_word_list, right_len_4)
{
    struct vector *v = init_word_list("lexicons/lex_first.txt", 4);
    cr_assert(v->size==8);
    vector_free(v, &free);
}

Test(init_word_list, right_word_4)
{
    struct vector *v = init_word_list("lexicons/lex_first.txt", 4);
    cr_assert(strcmp(v->data[0], "cork")==0);
    vector_free(v, &free);
}

Test(init_word_list, right_word_3)
{
    struct vector *v = init_word_list("lexicons/lex_first.txt", 3);
    cr_assert(strcmp(v->data[0], "ape")==0);
    vector_free(v, &free);
}
