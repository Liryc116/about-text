#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>

#include "../src/utils/vector.h"
#include "../src/prefix_trees/ptree.h"
#include "../src/prefix_trees/prefix_tree.h"

Test(add_word, add_1)
{
    struct ptree *t = ptree_new('\0', 0);

    add_word(t, "hand");

    cr_assert(t->nbchildren == 1);

    ptree_free(t);
}

Test(add_word, same_first)
{
    struct ptree *t = ptree_new('\0', 0);

    add_word(t, "hand");
    add_word(t, "handsome");

    cr_assert(t->nbchildren == 1);

    ptree_free(t);
}

Test(add_word, diff_first)
{
    struct ptree *t = ptree_new('\0', 0);

    add_word(t, "pretty");
    add_word(t, "handsome");

    cr_assert(t->nbchildren == 2);

    ptree_free(t);
}

Test(count_words, diff_first)
{
    struct ptree *t = ptree_new('\0', 0);

    add_word(t, "pretty");
    add_word(t, "handsome");

    cr_assert(count_words(t) == 2);

    ptree_free(t);
}

Test(count_words, same_first)
{
    struct ptree *t = ptree_new('\0', 0);

    add_word(t, "hand");
    add_word(t, "handsome");

    cr_assert(count_words(t)==2);

    ptree_free(t);
}

Test(build_tree, built)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    cr_assert(count_words(t)==11);

    ptree_free(t);
}

Test(search_word, in)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    cr_assert(search_word(t, "fancy"));
    cr_assert(search_word(t, "fan"));
    cr_assert(search_word(t, "fame"));

    ptree_free(t);
}

Test(search_word, out)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    cr_assert(!search_word(t, "pretty"));
    cr_assert(!search_word(t, "hand"));

    ptree_free(t);
}

Test(word_list, list)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    struct vector *v = word_list(t);
    cr_assert(v->size==11);

    vector_free(v, &free);

    ptree_free(t);
}

Test(completion, in)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    struct vector *v = completion(t, "fan");
    cr_assert(v->size==2);

    ptree_free(t);
    vector_free(v, &free);
}

Test(completion, out)
{
    struct ptree *t = buildtree("lexicons/wordList1.txt");

    struct vector *v = completion(t, "hand");
    cr_assert(v->size==0);

    vector_free(v, &free);

    ptree_free(t);
}
