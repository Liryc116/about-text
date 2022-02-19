#include "parser.h"

#include <stddef.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "utils/token.h"
#include "utils/htab.h"
#include "utils/string_manipulation.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif /* ! BUFFER_SIZE */

size_t shift_buffer(size_t len, size_t to_treat, int fd, char *buf)
{
    to_treat -= (len);
    memmove(buf, buf+len, to_treat);
    to_treat += read(fd, buf+to_treat, BUFFER_SIZE-to_treat);
    return to_treat;
}

struct htab *param_parser(char *filepath, char *attrib, char *bod, char *eod)
{
    struct htab *ht = htab_new();
    int fd = open(filepath, O_RDONLY);
    if(fd == -1)
        errx(1, "param_parser: could not open %s", filepath);

    size_t a_len = strlen(attrib);
    size_t eod_len = strlen(eod);
    size_t bod_len = strlen(bod);
    char buf[BUFFER_SIZE];
    size_t to_treat = read(fd, buf, BUFFER_SIZE);

    while(to_treat != 0)
    {
        char *end = strnstr(buf, attrib, BUFFER_SIZE);
        if(end==NULL)
            errx(1, "param_parser: could not find the name");

        *end = '\0';
        char *name = stracpy(buf);
        size_t len = strlen(name);

        struct pair *p = htab_get(ht, name);
        if(p==NULL)
        {
            htab_insert(ht, name, gram_token_new(name));
            p = htab_get(ht, name);
        }

        to_treat = shift_buffer(len+a_len, to_treat, fd, buf);

        for(int found_eod = 0; !found_eod; )
        {
            char *nbod = strnstr(buf, bod, BUFFER_SIZE);
            end = strnstr(buf, eod, BUFFER_SIZE);
            if(end!=NULL && end<=nbod)
            {
                found_eod = 1;
                *end = '\0';
                len = strlen(buf);
            }
            else if(nbod<end && nbod!=NULL)
            {
                end = nbod;
                *end = '\0';
                len = strlen(buf) + bod_len - eod_len;
            }
            else
                errx(1, "Could not find neither %s or %s", bod, eod);
            gram_token_add_poss(p->value, buf);
            to_treat = shift_buffer(len+eod_len, to_treat, fd, buf);
        }
    }

    close(fd);
    return ht;
}

// ebnf_str a string describing a rule in ebnf format
// returns a graph of the rule
void handle_ebnf(char *ebnf_str)
{
    // TODO
    if(ebnf_str==NULL)
        errx(1, "handle_ebnf: NULL string");
}

// return 0 if str does not pass the ebnf rule
int validate_ebnf(char *ebnf, struct token *tokens, size_t ntoken)
{
    // TODO
    size_t i;
    for(i=0; i<ntoken && ebnf[i]!='\0' && &tokens[i]!=NULL; i++);

    return i==ntoken;
}
