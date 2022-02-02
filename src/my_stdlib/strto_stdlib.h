#ifndef STRTO_STDLIB_H
#define STRTO_STDLIB_H

long my_strtol(const char *nptr, char **endptr, int base);

long long my_strtoll(const char *nptr, char **endptr, int base);

/*
double my_strtod(const char *nptr, char **endptr);

float my_strtof(const char *nptr, char **endptr);

long double my_strtold(const char *nptr, char **endptr);
*/

#endif /* ! STRTO_STDLIB_H */
