#include "graph.h"
#include <err.h>
#include <string.h>
#include <stdlib.h>

struct graph *graph_new(size_t order, int directed, char *labels)
{
    struct graph *g = malloc(sizeof(struct graph));
    if(g==NULL)
        errx(1, "graph_new: Not enough memory");

    g->order = order;
    g->directed = directed;
    if(labels!=NULL)
    {
        size_t len = strlen(labels)+1;
        g->labels = malloc(len);
        strncpy(g->labels, labels, len);
    }

    return g;
}

void graph_free(struct graph *g)
{
    if(g->labels!=NULL)
        free(g->labels);
    free(g);
}
