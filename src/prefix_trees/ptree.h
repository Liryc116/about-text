#ifndef PTREE_H
#define PTREE_H

#include <stddef.h>

struct ptree{
    char key;
    int is_final;
    struct ptree **children; // pointer array
    size_t nbchildren;
};

struct ptree *ptree_new(char c, int is_final);

void ptree_insert_children(struct ptree *t, size_t n, struct ptree *child);

void ptree_free(struct ptree *t);

#endif /* ! PTREE_H */
