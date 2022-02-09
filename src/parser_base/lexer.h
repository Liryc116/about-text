#ifndef LEXER_H
#define LEXER_H

/**
** file_path: a path to the file with the lexer rules
** It use regex, look at the local README for the format file to understand
*/
void param_lexer(char *file_path, char *attris, char *eod);


/**
** str the string to tokenize
** len final value: number of token returned
*/
struct token *tokenize(char *str, size_t *len);

#endif
