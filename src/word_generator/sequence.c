#include "sequence.h"

#include "../utils/matrix.h"

#include <stdio.h>
#include <err.h>

#define BUFFER_SIZE 256

void update_mat(struct matrix *m, char *word)
{
    size_t prev = 26;
    size_t current = 26;

    for(size_t i = 0; word[i]!='\0'; i++)
    {
        current = word[i];
        if(current>='a' && current<='z')
            current-='a';
        else if(current>='A' && current<='Z')
            current-='A';
        else
            current = 26;

        if(current != 26 || prev!=26)
            matrix_add_at(m, current, prev, 1);
        prev = current;
    }

    current = 26;
    if(prev!=26)
        matrix_add_at(m, current, prev, 1);
}

void to_probability(struct matrix *m)
{
    for(size_t i = 0; i<m->height; i++)
    {
        double sum = matrix_row_sum(m, i);

        if(sum==0)
            m->data[26+i*m->width] = 1;
        else
        {
            for(size_t k = 0; k<m->width; k++)
                m->data[k+i*m->width]/=sum;
        }
    }
}

void print_sequence(struct matrix *m)
{
    printf("    ");
    for(char i = 0; i<26; i++)
        printf(" %c  ", i+'a');
    printf("*\n");

    for(char i = 0; i<27; i++)
    {
        printf("%c | ", i+'a');
        for(size_t k = 0; k<27; k++)
            printf("%3.0f ", 100*m->data[k+i*m->width]);
        printf("\n");
    }
}

struct matrix *get_sequence(char *path)
{
    FILE *fp = fopen(path, "r");
    if(fp==NULL)
        errx(1, "Could not open the file:%s", path);

    char buff[BUFFER_SIZE] = {0};
    struct matrix *m = matrix_new(27, 27);

    while(fgets(buff, BUFFER_SIZE, fp))
        update_mat(m, buff);

    fclose(fp);

    to_probability(m);

    return m;
}
