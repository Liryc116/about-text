#include "lexer.h"
#include "utils/token.h"
#include "utils/htab.h"
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif /* ! BUFFER_SIZE */

struct htab *param_lexer(char *file_path, char *attrib, char *eod)
{
    int fd = open(file_path, O_RDONLY);
    if(fd==-1)
        errx(1, "param_lexer: could not open %s", file_path);

    struct htab *ht = htab_new();
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
        size_t len = strlen(buf)+1;
        char *name = malloc(len);
        strncpy(name, buf, len);

        to_treat-= (len + a_len);
        memmove(buf, buf+len+a_len, to_treat);

        to_treat += read(fd, buf+len+a_len, BUFFER_SIZE-to_treat);

        end = strstr(buf, eod);
        if(end==NULL)
            errx(1, "param_lexer: could not find the end of declaration");
        *end = '\0';
        len = strlen(buf);
        to_treat -= (len + eod_len);

        htab_insert(ht, name, lex_token_new(name, buf));

        memmove(buf, buf+len+eod_len, to_treat);
        to_treat += read(fd, buf+to_treat, BUFFER_SIZE-to_treat);
    }

    close(fd);

    return ht;
}

/*
struct vector *tokenize(struct desc_vector *v, char *str)
{
    struct vector *res = vector_new();

    size_t i = 0;
    size_t len = strlen(str);
    regmatch_t match[1];
    char *s = str;
    char *found = NULL;

    while(i<len)
    {
        size_t found_kind = 0;
        for(size_t j = 1; found_kind==0 && j<v->size; j++)
        {
            size_t ret = regexec(&v->data[j]->reg, s, 1, match, 0);
            if(ret!=REG_NOMATCH && match[0].rm_so==0)
            {
                size_t len = match[0].rm_eo;
                found = malloc(len);
                strncpy(found, s, len);
                found[len-1] = '\0';
                s+=len;
                found_kind = j;
            }
        }

        if(found_kind!=0 || v->size==0 || v->data[v->size-1]->kind!=0)
        {
            size_t tmp_len = (match[0].rm_eo-match[0].rm_so)
            char *found_str = calloc(tmp_len, sizeof(char));

            token_new(found_kind, )
                vector push
        }
        else
        {
            if(v->size==0 || v->data[v->size-1]->kind!=0)
            {}
            else
                //modif previous
        }

        tmp[0] = '\0';
    }

    return res;
}
*/
