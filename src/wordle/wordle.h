#ifndef WORDLE_H
#define WORDLE_H

#include "../utils/vector.h"

#include <stddef.h>

// We assume strlen(expected) == strlen(received)
int *evaluate_answer(char *expected, char *received);

// Takes a path to a lexicon and a size
// return the list of all the word of strlen==size
struct vector *init_word_list(char* path, size_t size);

#endif /* ! WORDLE_H */
