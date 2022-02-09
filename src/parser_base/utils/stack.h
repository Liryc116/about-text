#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct heap
{
    void *data;
    struct heap *next;
};

struct heap *heap_new(void);

void heap_push(struct heap *h, void *data, size_t data_size);

void *heap_pop(struct heap *h);

void heap_free(struct heap *h);

#endif /* ! STACK_H */
