#ifndef GENERATOR_H
#define GENERATOR_H

#include <stddef.h>

#include "../utils/matrix.h"

char *gen_word(struct matrix *seq, size_t max_len);

char *gen_exact_word(struct matrix *sequence, size_t exact_len);

#endif
