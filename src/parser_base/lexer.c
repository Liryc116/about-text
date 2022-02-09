#include "lexer.h"
#include "utils/token.h"
#include <string.h>
#include <err.h>

#ifndef
#define BUFFER_SIZE 256
#endif

/*
    void ebnf_to_regex(char *ebnf)
{

}
*/

struct vector *param_lexer(char *file_path, char *attrib, char *eod)
{
    int fd = open(file_path, O_RDONLY);
    if(fd==-1)
        errx(1, "param_lexer: could not open");

    struct vector *rules = vector_new();
    size_t a_len = strlen(attrib);
    size_t eod_len = strlen(eod);

    char buf[BUFFER_SIZE];
    size_t check = read(fd, buf, to_read);
    size_t to_treat = check;
    while(to_treat != 0)
    {
        char *end = strstr(buff, attrib);
        *end = '\0';
        size_t len = strlen(buf);
        char *name = malloc(len);
        strcpy(name, buf);
        memmove(buf, buf+len+a_len, check-len-a_len);

        if(check==BUFFER_SIZE)
            check = read(fd, buf+len+a_len, BUFFER_SIZE-len-a_len);

        char *end = strstr(buf, eod);
        *end = '\0';
        len = strlen(buf);
        regex_t rule;
        int get_err = regcomp(&rule, buf, REG_EXTENDED);
        vector_append(rules, token_desk_new(name, NULL, rule));

        memmove(buf, buf+len+eod_len, check-len-eod_len);
    }

    return rules;
}

struct token *tokenize(char *str, size_t *len)
{


    return NULL;
}
