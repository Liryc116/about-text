#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <regex.h>
#include "../../src/parser_base/lexer.h"
#include "../../src/parser_base/utils/token.h"
#include "../../src/parser_base/utils/htab.h"

Test(setup, runs)
{
    struct htab *ht = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");
    cr_assert(ht!=NULL);

    htab_free(ht, &lex_token_free);
}

Test(setup, correct)
{
    struct htab *ht = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");

    cr_assert(htab_get(ht, "random")==NULL);
    cr_assert(htab_get(ht, "all_digits")!=NULL);
    cr_assert(htab_get(ht, "Non-nul-digits")!=NULL);
    cr_assert(htab_get(ht, "operators")!=NULL);

    htab_free(ht, &lex_token_free);
}

Test(setup, recognize)
{
    struct htab *ht = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");

    char *str = " 42? or what 30";
    regmatch_t match[1];
    regoff_t len;
    regex_t reg = ((struct lex_token *) htab_get(ht, "Non-nul-digits")->value)->reg;
    int get_err = regexec(&reg, str, 1, match, 0);

    len = match[0].rm_eo - match[0].rm_so;
    cr_assert(get_err==0);
    cr_assert(strncmp("42", str+match[0].rm_so, len)==0);

    str+= match[0].rm_eo;
    get_err = regexec(&reg, str, 1, match, 0);
    len = match[0].rm_eo - match[0].rm_so;

    cr_assert(get_err==0);
    cr_assert(strncmp("2", str+match[0].rm_so, len)==0);

    str+= match[0].rm_eo;
    get_err = regexec(&reg, str, 1, match, 0);
    len = match[0].rm_eo - match[0].rm_so;

    cr_assert(get_err==0);
    cr_assert(strncmp("3", str+match[0].rm_so, len)==0);

    htab_free(ht, &lex_token_free);
}
