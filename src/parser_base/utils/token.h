#ifndef TOKEN_H
#define TOKEN_H

#include <regex.h>
#include <stddef.h>

// If ebnf is NULL it is considered as a regex/lexer token
// Else it is considered an ebnf/parse token
struct lex_token
{
    char *name;
    regex_t reg;
};

struct gram_token
{
    char *name;
    size_t nposs;
    size_t capacity;
    char **poss;
};

struct token
{
    char *name;
    char *str;
};

// Creates a vector of token_description
// and set the data[0] to the "other" token

struct lex_token *lex_token_new(char *name, char *regex_str);

void lex_token_free(void *tok);

struct gram_token *gram_token_new(char *name);

void gram_token_free(void *tok);

void gram_token_add_poss(struct gram_token *token, char *poss);

struct token *token_new(char *name, char *str);

#endif /* ! TOKEN_H */
