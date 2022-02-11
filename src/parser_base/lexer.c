#include "lexer.h"
#include "utils/token.h"
#include "utils/vector.h"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif /* ! BUFFER_SIZE */

struct desc_vector *param_lexer(char *file_path, char *attrib, char *eod)
{
    int fd = open(file_path, O_RDONLY);
    if(fd==-1)
        errx(1, "param_lexer: could not open %s", file_path);

    struct desc_vector *rules = desc_vector_init();
    size_t a_len = strlen(attrib);
    size_t eod_len = strlen(eod);

    char buf[BUFFER_SIZE];
    size_t to_treat = read(fd, buf, BUFFER_SIZE);
    while(to_treat != 0)
    {
        char *end = strstr(buf, attrib);
        if(end==NULL)
            errx(1, "param_lexer: could not find the name");

        *end = '\0';
        size_t len = strlen(buf);
        char *name = malloc(len+1);
        strcpy(name, buf);
        name[len]='\0';

        to_treat-= (len + a_len);
        memmove(buf, buf+len+a_len, to_treat);

        to_treat += read(fd, buf+len+a_len, BUFFER_SIZE-to_treat);

        end = strstr(buf, eod);
        if(end==NULL)
            errx(1, "param_lexer: could not find the end of declaration");
        *end = '\0';
        len = strlen(buf);
        regex_t rule;
        to_treat -= (len + eod_len);

        int get_err = regcomp(&rule, buf, REG_EXTENDED);
        if(get_err == -1)
            errx(1, "could not compose a RegEx from: %s", buf);
        desc_vector_append(rules, name, NULL, rule);

        memmove(buf, buf+len+eod_len, to_treat);
        to_treat += read(fd, buf+to_treat, BUFFER_SIZE-to_treat);
    }

    close(fd);

    return rules;
}

struct token *tokenize(struct desc_vector *v, char *str, size_t *len)
{
    while(len!=0 && str!=NULL)
    {
        return token_new(v, NULL, str);
    }
    return NULL;
}
