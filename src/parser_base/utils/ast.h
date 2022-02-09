#ifndef AST_H
#define AST_H

#include <stddef.h>
#include "vector.h"
#include "token.h"

struct ast
{
    struct token *value;
    struct ast *children;
    size_t capacity;
    size_t size;
};

//new

//append children

#endif /* ! AST_H */
