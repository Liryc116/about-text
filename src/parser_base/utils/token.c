#include "token.h"
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

void desc_vector_double_capacity(struct desc_vector *v)
{
    v->capacity*=2;
    v->data = reallocarray(v->data,
            sizeof(struct token_description *), v->capacity);
    if(v->data==NULL)
        errx(1, "Not enough memory");
}

struct token_description *token_desc_new(size_t n,
        char *name, char *ebnf, regex_t reg)
{
    struct token_description *desc = malloc(sizeof(struct token_description));
    if(desc==NULL)
        errx(1, "Not enough memory");

    desc->name = name;
    desc->kind = n;
    desc->ebnf = NULL;

    if(ebnf!=NULL)
    {
        desc->ebnf=calloc(strlen(ebnf)+1, sizeof(char));
        strcpy(desc->ebnf, ebnf);
    }
    else
        desc->reg = reg;

    return desc;
}

void desc_vector_append(struct desc_vector *v,
                                char *name, char *ebnf, regex_t reg)
{
    if(v->size==v->capacity)
        desc_vector_double_capacity(v);

    struct token_description *t = token_desc_new(v->size, name, ebnf, reg);
    v->data[v->size] = t;
    v->size+=1;
}

struct desc_vector *desc_vector_init(void)
{
    struct desc_vector *vect = malloc(sizeof(struct desc_vector));

    vect->capacity = 2;
    vect->size = 0;
    vect->data = malloc(2*sizeof(struct token_description *));

    return vect;
}

void token_desc_free(struct token_description *t)
{
    free(t->name);
    if(t->ebnf!=NULL)
        free(t->ebnf);
    else
        regfree(&t->reg);

    free(t);
}

void desc_vector_free(struct desc_vector *v)
{
    for(size_t i = 0; i<v->size; i++)
        token_desc_free(v->data[i]);
    free(v->data);
    free(v);
}

struct token *token_new(struct desc_vector *v, char *name, char *str)
{
    struct token *t = malloc(sizeof(struct token));
    for(size_t i = 0; i<v->size; i++)
    {
        if(strcmp(name, v->data[i]->name)==0)
            t->kind = i;
    }
    t->str = str;
    return t;
}
