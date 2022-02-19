#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include <stddef.h>

// Finds the first occurrence of the substring needle in,
// atmost the n first bytes of the string haystack
// The terminating null bytes ('\0') are not compared.
char *strnstr(char *haystack, char *needle, size_t n);

size_t strncspn(const char *s, const char *reject, size_t n);

// Copy str in a new string and allocates it. The caller should free it
char *stracpy(char *src);

// Returns 1 if str is only capital letters
int is_all_capital(char *str);

// ignored chars are ' ' and '\t'
char *skip_ignored(char *str);

#endif
