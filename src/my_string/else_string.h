#ifndef ELSE_STRING_H
#define ELSE_STRING_H

#include "my_string.h"

size_t my_strlen(const char *str);

char *my_strstr(const char *haystack, const char *needle);

size_t my_strspn(const char *s, const char *accept);

char *my_strrchr(const char *s, int c);

char *my_strtok(char *str, const char *delim);

#endif /* ! ELSE_STRING_H */
