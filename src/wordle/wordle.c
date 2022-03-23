#include "wordle.h"

#include "../utils/xmalloc.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

#define BUFFER_SIZE 256

int right_word(int *eval, size_t size)
{
    for(size_t i = 0; i<size; i++)
    {
        if(eval[i]!=GREEN)
            return 0;
    }

    return 1;
}

void print_color(char c, int color)
{
    if(color == GRAY)
        printf("\033[0;37m"); // White
    else if(color == YELLOW)
        printf("\033[0;33m"); // Yellow
    else
        printf("\033[0;32m"); // Green

    printf("%c", c);
    printf("\033[0m"); //Resets the text to default color
}

void print_evaluation(char* str, int *eval)
{
    for(size_t i = 0; str[i]!='\0'; i++)
        print_color(str[i], eval[i]);
    printf("\n");
}

// We assume strlen(expected) == strlen(received)
int *evaluate_answer(char *expected, char *received)
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
                result[i] = YELLOW;
                if(k==i)
                    result[i]= GREEN;
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

        if(buff[size]=='\n')
        {
            buff[size] = '\0';
            vector_push(res, buff, sizeof(char)*(size+1));
        }
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

size_t play_word(char *expected, size_t size, size_t tries)
{
    char *answer = xcalloc(size+1, sizeof(char));
    int *eval = NULL;

    do
    {
        printf("You have %lu attenpts left\n", tries);
        printf("Enter a %lu letters long word:", size);

        scanf("%s", answer);
        eval = evaluate_answer(expected, answer);
        print_evaluation(answer, eval);
        if(!right_word(eval, size))
            tries--;
        else
        {
            free(eval);
            break;
        }

        free(eval);
    }
    while(tries!=0);

    printf("\nThe right answer is: %s\n", expected);

    free(answer);

    return tries;
}

void wordle_main(void)
{
    size_t tries = 6;
    size_t size = 5;
    struct vector *v = init_word_list("lexicons/lex_all.txt", size);

    char exit[6] = {0};
    while(strcmp(exit, "exit")!=0)
    {
        size_t score = play_word(pick_word(v), size, tries);
        printf("Your score is: %lu\n\n", score);
        printf("Do you want to quit?\nWrite 'exit' if you want to exit the game\n");
        scanf("%s", exit);
    }

    vector_free(v, &free);
}
