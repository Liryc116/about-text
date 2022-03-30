#include "ptree.h"

#include "../utils/xmalloc.h"

#include <stdlib.h>

struct ptree *ptree_new(char c, int is_final)
{
    struct ptree *t = xcalloc(1, sizeof(struct ptree));

    t->key = c;
    t->is_final = is_final;

    return t;
}

void ptree_insert_children(struct ptree *t, size_t n, struct ptree *child)
{
    if(n>t->nbchildren)
        return;

    t->nbchildren+=1;
    t->children = xreallocarray(t->children, t->nbchildren,
                                                sizeof(struct ptree *));


    for(size_t i = t->nbchildren-1; i>n; i--)
        t->children[i] = t->children[i-1];
    t->children[n] = child;
}

void ptree_free(struct ptree *t)
{
    for(size_t i = 0; i<t->nbchildren; i++)
        ptree_free(t->children[i]);

    free(t->children);
    free(t);
}
