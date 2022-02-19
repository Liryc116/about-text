#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include "vector.h"

struct graph
{
    size_t order;
    int directed;
    struct vector **adjlist;
    char *labels;
};

struct graph *graph_new(size_t order, int directed, char *labels);

void graph_free(struct graph *g);

#endif /* ! GRAPH_H */
