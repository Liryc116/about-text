#ifndef TOKEN_H
#define TOKEN_H

#include <regex.h>
#include <stddef.h>

// If ebnf is NULL it is considered as a regex/lexer token
// Else it is considered an ebnf/parse token
struct token_description
{
    size_t kind;
    char *name;
    char *ebnf;
    regex_t reg;
};

struct desc_vector
{
    size_t capacity;
    size_t size;
    struct token_description **data;
};

struct token
{
    size_t kind;
    char *str;
};

// Creates a vector of token_description
// and set the data[0] to the "other" token
struct desc_vector *desc_vector_init(void);

void desc_vector_append(struct desc_vector *v,
                                char *name, char *ebnf, regex_t reg);

struct token *token_new(struct desc_vector *v, char *name, char *str);

#endif /* ! TOKEN_H */
