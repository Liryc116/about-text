#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

struct lex_token *lex_token_new(char *name, char *regex_str)
{
    if(name==NULL || regex_str == NULL)
        errx(1, "lex_token_new: one or more NULL args");

    struct lex_token *t = malloc(sizeof(struct lex_token));
    if(t==NULL)
        errx(1, "Not enough memory");

    if(regcomp(&t->reg, regex_str, REG_EXTENDED)!=0)
        errx(1, "Could not compile the regex %s", regex_str);
    t->name = name;

    return t;
}

void lex_token_free(void *tok)
{
    struct lex_token *t = tok;
    free(t->name);
    regfree(&t->reg);
    free(t);
}

struct gram_token *gram_token_new(char *name)
{
    struct gram_token *gt = malloc(sizeof(struct gram_token));
    if(gt==NULL)
        errx(1, "Not enough memory");

    gt->name = name;
    gt->poss = calloc(2, sizeof(char *));
    gt->nposs = 0;
    gt->capacity = 2;

    return gt;
}

void gram_token_free(void *tok)
{
    struct gram_token *t = tok;
    for(size_t i = 0; i<t->nposs; free(t->poss[i]), i++);
    free(t->poss);
    free(t);
}

static void gram_token_double_capacity(struct gram_token *gt)
{
    gt->capacity *=2;
    gt->poss = reallocarray(gt->poss, gt->capacity, sizeof(char *));
}

void gram_token_add_poss(struct gram_token *token, char *poss)
{
    if(poss==NULL)
        errx(1, "gram_token_add_poss: poss is NULL");
    if(token->nposs==token->capacity)
        gram_token_double_capacity(token);

    size_t len = strlen(poss);
    token->poss[token->nposs] = calloc(len+1, sizeof(char));
    if(token->poss[token->nposs]==NULL)
        errx(1, "Not enough memory");
    token->poss[token->nposs]=strcpy(token->poss[token->nposs], poss);
    token->nposs +=1;
}

struct token *token_new(char *name, char *str)
{
    struct token *t = malloc(sizeof(struct token));
    t->str = str;
    t->name = name;
    return t;
}
