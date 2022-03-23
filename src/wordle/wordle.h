#ifndef WORDLE_H
#define WORDLE_H

#include "../utils/vector.h"

#include <stddef.h>

#define GRAY 0
#define YELLOW 1
#define GREEN 2

// We assume strlen(expected) == strlen(received)
int *evaluate_answer(char *expected, char *received);

// Takes a path to a lexicon and a size
// return the list of all the word of strlen==size
struct vector *init_word_list(char* path, size_t size);

// Returns a word form the list
char *pick_word(struct vector *v);

void wordle_main(void);

#endif /* ! WORDLE_H */
