#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "../../src/parser_base/lexer.h"
#include "../../src/parser_base/utils/token.h"

Test(setup, runs)
{
    struct desc_vector *v = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");
    cr_assert(v!=NULL);

    desc_vector_free(v);
}

Test(setup, correct)
{
    struct desc_vector *v = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");

    cr_assert(v->size==4);
    cr_assert(v->capacity==4);
    cr_assert(strcmp(v->data[1]->name, "Non-nul-digits")==0);
    cr_assert(v->data[1]->kind==1);

    desc_vector_free(v);
}
