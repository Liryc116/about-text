#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "../../src/parser_base/lexer.h"
#include "../../src/parser_base/utils/token.h"

Test(setupt, runs)
{
    struct desc_vector *v = param_lexer("src/parser_base/lexer_rules",
            " := ", ";\n");
    cr_assert(v!=NULL);

    desc_vector_free(v);
}
