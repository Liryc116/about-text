#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

struct ast{
    struct token *data
    struct ast *left, *right;
}

#endif /* ! PARSER_H */
