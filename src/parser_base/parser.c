#include "parser.h"
#include <stddef.h>
#include <err.h>
#include "utils/token.h"

// ebnf_str a string describing a rule in ebnf format
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
