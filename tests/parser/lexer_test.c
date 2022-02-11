#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <regex.h>
#include "../../src/parser_base/lexer.h"
#include "../../src/parser_base/utils/token.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

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

Test(setup, recognize)
{
    struct desc_vector *v = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");

    char *str = " 42? or what 30";
    regmatch_t match[1];
    regoff_t len;
    int get_err = regexec(&v->data[1]->reg, str, 1, match, 0);

    len = match[0].rm_eo - match[0].rm_so;
    cr_assert(get_err==0);
    cr_assert(strncmp("42", str+match[0].rm_so, len)==0);

    str+= match[0].rm_eo;
    get_err = regexec(&v->data[1]->reg, str, 1, match, 0);
    len = match[0].rm_eo - match[0].rm_so;

    cr_assert(get_err==0);
    cr_assert(strncmp("2", str+match[0].rm_so, len)==0);

    str+= match[0].rm_eo;
    get_err = regexec(&v->data[1]->reg, str, 1, match, 0);
    len = match[0].rm_eo - match[0].rm_so;

    cr_assert(get_err==0);
    cr_assert(strncmp("3", str+match[0].rm_so, len)==0);
    desc_vector_free(v);
}
