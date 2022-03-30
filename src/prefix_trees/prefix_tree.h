#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include "ptree.h"
#include "../utils/vector.h"

size_t count_words(struct ptree *t);

size_t longest_word_len(struct ptree *t);

struct vector *word_list(struct ptree *t);

int search_word(struct ptree *t, char *str);

struct vector *completion(struct ptree *t, char *prefix);

void add_word(struct ptree *t, char *str);

struct ptree *buildtree(char *filepath);

#endif /* ! PREFIX_TREE_H */
