#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <regex.h>
#include <string.h>
#include "../../src/parser_base/parser.h"
#include "../../src/parser_base/utils/token.h"
#include "../../src/parser_base/utils/htab.h"

Test(param_parser, runs)
{
    struct htab *ht = param_parser("src/parser_base/parser_grammar", ":", "\n",
                    "\n\n");

    cr_assert(ht!=NULL);

    htab_free(ht, &gram_token_free);
}

Test(param_parser, read_all)
{
    struct htab *ht = param_parser("src/parser_base/parser_grammar", ":", "\n",
                    "\n\n");

    cr_assert(ht->size!=0);

    htab_free(ht, &gram_token_free);
}

Test(param_parser, read_correct)
{
    struct htab *ht = param_parser("src/parser_base/parser_grammar", ":", "\n",
                    "\n\n");

    struct pair *p = htab_get(ht, "input");
    cr_assert(p!=NULL);

    struct gram_token *gt = p->value;
    cr_assert(strcmp(gt->name, "input")==0);
    cr_assert(gt->nposs==4);

    htab_free(ht, &gram_token_free);
}
