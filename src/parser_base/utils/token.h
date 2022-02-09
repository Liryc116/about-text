#ifndef TOKEN_H
#define TOKEN_H

#include <regex.h>

struct token_description
{
    int kind;
    char *name;
    char *ebnf;
    regex_t reg;
};

struct token
{
    int kind;
    char *str;
};

void token_add_kind(char *name);

struct token_description *token_desc_new(char *name, char *ebnf, regex_t reg);

#endif /* ! TOKEN_H */
