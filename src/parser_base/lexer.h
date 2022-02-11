#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
/**
** file_path: a path to the file with the lexer rules
** It use regex, look at the local README for the format file to understand
*/
struct desc_vector *param_lexer(char *file_path, char *attrib, char *eod);


/**
** str the string to tokenize
** len final value: number of token returned
*/
struct token *tokenize(struct desc_vector *v, char *str, size_t *len);

#endif
