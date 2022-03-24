#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "../utils/matrix.h"

void to_probability(struct matrix *m);

void print_sequence(struct matrix *m);

struct matrix *get_sequence(char *path);

#endif /* ! SEQUENCE_H */
