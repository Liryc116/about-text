#include <stdlib.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/my_string/my_string.h"

Test(my_strtok, tok_00)
{
    char str1[80] = "This is - www.tutorialspoint.com - website";
    char str2[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";

    /* get the first token */
    char *token = my_strtok(str1, s);
    char *t = strtok(str2, s);

    /* walk through other tokens */
    while( token != NULL && t!=NULL)
    {
        cr_assert(!strcmp(token, t));
        //printf("%s\n", token);

        token = my_strtok(NULL, s);
        t = strtok(NULL, s);
    }

    cr_assert(token==NULL && t==NULL);
}

Test(my_strtok, tok_01)
{
    char str1[80] = "abzerqw abfepsfc bpr abktg";
    char str2[80] = "abzerqw abfepsfc bpr abktg";
    const char s[3] = "ab";

    /* get the first token */
    char *token = my_strtok(str1, s);
    char *t = strtok(str2, s);

    /* walk through other tokens */
    while( token != NULL && t!=NULL)
    {
        cr_assert(!strcmp(token, t));
        //printf("%s\n", token);

        token = my_strtok(NULL, s);
        t = strtok(NULL, s);
    }

    cr_assert(token==NULL && t==NULL);
}

Test(my_strtok, tok_02)
{
    char str1[80] = "abzerqw abfepsfc bpr abktg";
    char str2[80] = "abzerqw abfepsfc bpr abktg";
    const char s1[3] = "ab";
    const char s2[2] = "a";

    /* get the first token */
    char *token = my_strtok(str1, s1);
    char *t = strtok(str2, s1);

    /* walk through other tokens */
    while( token != NULL && t!=NULL)
    {
        cr_assert(!strcmp(token, t));
        //printf("%s\n", token);

        token = my_strtok(NULL, s2);
        t = strtok(NULL, s2);
    }

    cr_assert(token==NULL && t==NULL);
}
