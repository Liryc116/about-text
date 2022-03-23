#include "wordle.h"

#include "../utils/xmalloc.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

#define GRAY 0
#define YELLOW 1
#define GREEN 2

#define BUFFER_SIZE 256

int *evalute_answer(char *expected, char *received)
{
    size_t len = strlen(expected);
    int *result = xcalloc(len, sizeof(int));
    int *used = xcalloc(len, sizeof(int));

    for(size_t i = 0; i<len; i++)
    {
        for(size_t k = 0; k<len; k++)
        {
            if(!used[k] && received[i]==expected[k])
            {
                used[k]=1;
                result[k] = YELLOW;
                if(k==i)
                    result[k]= GREEN;
            }
        }
    }

    free(used);

    return result;
}

struct vector *init_word_list(char* path, size_t size)
{
    if(size>=BUFFER_SIZE)
        errx(1, "the size %lu is too big. Buffer size is only %d",
                size, BUFFER_SIZE);

    FILE *fp = fopen(path, "r");
    if(fp==NULL)
        errx(1, "Could not open the file:%s", path);

    char buff[BUFFER_SIZE] = {0};

    struct vector *res = vector_new();

    while(!feof(fp))
    {
        fgets(buff, BUFFER_SIZE, fp);

        if(strlen(buff)==size)
            vector_push(res, buff, sizeof(char)*(size+1));
    }

    fclose(fp);

    return res;
}

char *pick_word(struct vector *v)
{
    srand(time(0));
    size_t n = rand() % v->size;

    return v->data[n];
}
