#include "prefix_tree.h"

#include "../utils/xmalloc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

size_t count_words(struct ptree *t)
{
   size_t res = 0;
   if(t->is_final)
       res = 1;

   for(size_t i = 0; i<t->nbchildren; i++)
       res += count_words(t->children[i]);

   return res;
}

static size_t my_max(size_t a, size_t b)
{
    if(a>b)
        return a;
    return b;
}

size_t longest_word_len(struct ptree *t)
{
   size_t res = 0;

   for(size_t i = 0; i<t->nbchildren; i++)
       res = my_max(res, count_words(t->children[i]));

   return res+1;
}

char *__word_list(struct ptree *t, struct vector *v, char *pref)
{
    size_t len = strlen(pref);
    pref = xreallocarray(pref, len+2, sizeof(char));
    pref[len] = t->key;
    pref[len+1] = '\0';

    if(t->is_final)
        vector_push(v, pref, len+2);

    for(size_t i = 0; i<t->nbchildren; i++)
        pref = __word_list(t->children[i], v, pref);

    pref[len] = '\0';
    return pref;
}

struct vector *word_list(struct ptree *t)
{
    struct vector *v = vector_new();

    char *pref = xcalloc(1, sizeof(char));
    pref = __word_list(t, v, pref);

    free(pref);
    return v;
}

static size_t bin_search(struct ptree *t, char c)
{
    int a = 0;
    int b = t->nbchildren;

    while(a<b)
    {
        size_t mid = a + (b-a)/2;
        if(t->children[mid]->key==c)
            return mid;
        else if(t->children[mid]->key<c)
            a = mid + 1;
        else
            b = mid;
    }

    return b;
}

int search_word(struct ptree *t, char *str)
{
    if(str[0]=='\0')
        return t->is_final;

    size_t n = bin_search(t, str[0]);
    if(n>=t->nbchildren || t->children[n]->key != str[0])
        return 0;

    return search_word(t->children[n], str+1);
}

static struct ptree *completion_subt(struct ptree *t, char *prefix)
{
    if(prefix[0]=='\0')
        return t;

    size_t n = bin_search(t, prefix[0]);
    if(n>=t->nbchildren || t->children[n]->key != prefix[0])
        return NULL;

    return completion_subt(t->children[n], prefix+1);
}

struct vector *completion(struct ptree *t, char *prefix)
{
    struct vector *v = vector_new();

    struct ptree *subt = completion_subt(t, prefix);
    size_t len = strlen(prefix);
    char *w = xmalloc(len*sizeof(char));
    strncpy(w, prefix, len);
    if(len>=1)
        w[len-1] = '\0';

    if(subt!=NULL)
        w=__word_list(subt, v, w);

    free(w);

    return v;
}

void add_word(struct ptree *t, char *str)
{
    struct ptree *tmp = t;
    size_t n = 0;

    if(str[0]=='\0')
    {
        t->is_final = 1;
        return;
    }


    if(t->nbchildren==0)
        ptree_insert_children(tmp, n, ptree_new(str[0], 0));
    else
    {
        n = bin_search(t, str[0]);
        if(n>=t->nbchildren || t->children[n]->key != str[0])
            ptree_insert_children(tmp, n, ptree_new(str[0], 0));
    }

    add_word(t->children[n], str+1);
}

struct ptree *buildtree(char *filepath)
{
    FILE *fp = fopen(filepath, "r");

    struct ptree *t = ptree_new('\0', 0);
    char buff[BUFFER_SIZE] = {0};

    while(fgets(buff, BUFFER_SIZE, fp))
    {
        size_t len = strlen(buff);
        if(len!=0 && buff[len-1]=='\n')
            buff[len-1] = '\0';

        add_word(t, buff);
    }

    fclose(fp);

    return t;
}
