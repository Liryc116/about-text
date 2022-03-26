#include "generator.h"

#include "sequence.h"
#include "../utils/matrix.h"
#include "../utils/xmalloc.h"

#include <stdlib.h>
#include <stdio.h>

// Will generate a word of length max_len at most
char *gen_word(struct matrix *seq, size_t max_len)
{
    if(max_len==0)
        return NULL;

    char *res = xcalloc(max_len+1, sizeof(char));

    size_t len = 0;
    char prev = 26;

    do
    {
        double prob = ((double) rand()) / RAND_MAX;

        for(size_t i = 0; i<27; i++)
        {
            double letter_prob =seq->data[prev*seq->width+i];
            if(prob<=letter_prob)
            {
                prev = i;
                if(i!=26)
                    res[len] = i + 'a';
                i = 27;
            }
            else
                prob-=letter_prob;
        }

        len++;
    }
    while(max_len!=len && prev!=26);

    return res;
}

// Will generate a word of length exact_len exactly
char *gen_exact_word(struct matrix *sequence, size_t exact_len)
{
    if(exact_len==0)
        return NULL;

    char *res = xcalloc(exact_len+1, sizeof(char));

    size_t len = 0;
    char prev = 26;

    do
    {
        double eow_prob = sequence->data[26+prev*sequence->width];
        double prob = ((double) rand()) / RAND_MAX;
        prob*=(1-eow_prob);

        for(size_t i = 0; i<27; i++)
        {
            double letter_prob =sequence->data[prev*sequence->width+i];
            if(prob<=letter_prob)
            {
                prev = i;
                res[len] = i + 'a';
                i = 27;
            }
            else
                prob-=letter_prob;
        }

        len++;
    }
    while(exact_len>len);

    return res;
}
