#include "matrix.h"

#include "xmalloc.h"

#include <stdlib.h>
#include <err.h>

struct matrix* matrix_new(size_t width, size_t height)
{
    struct matrix *matrix = xmalloc(sizeof(struct matrix));

    matrix->width = width;
    matrix->height = height;
    matrix->data_size = sizeof(int);
    matrix->data = xmalloc(width*height * sizeof(double));

    for(size_t i = 0; i < width*height; i++)
        matrix->data[i] = 0;

    return matrix;
}

double matrix_col_sum(struct matrix *m, size_t n)
{
    if(n>=m->width)
        return 0;

    double res = 0;
    for(size_t i = 0; i<m->height; res+=m->data[i*m->width+n], i++);

    return res;
}

double matrix_row_sum(struct matrix *m, size_t n)
{
    if(n>=m->height)
        return 0;

    double res = 0;
    for(size_t i = 0; i<m->width; res+=m->data[n*m->width+i], i++);

    return res;
}

void matrix_add_at(struct matrix *m, size_t i, size_t j, double val)
{
    if(m->width<=i || m->height<=j)
        errx(1, "Incorrect insert coordinates, i=%lu, j=%lu", i, j);
    m->data[i+j*m->width]+=val;
}

void matrix_scalar_mult(struct matrix *m, int scalar)
{
    for(size_t i = 0; i<m->width*m->height; m->data[i]*=scalar, i++);
}

struct matrix* matrix_mult
                        (struct matrix *m1, struct matrix *m2)
{
    if(m1->width!=m2->height)
        return NULL;

    struct matrix *res = matrix_new(m2->width, m1->height);

    for(size_t i = 0; i<m1->height; i++)
    {
        for(size_t j = 0; j<m2->width; j++)
        {
            for(size_t k = 0; k<m1->width; k++)
                res->data[i*m2->width+j]+=m1->data[i*m1->width+k]
                                            *m2->data[k*m2->width+j];
        }
    }

    return res;
}

void matrix_sum(struct matrix *m1, struct matrix *m2)
{
    if(m1->width!=m2->width || m1->height!=m2->height)
        return;


    for(size_t i = 0; i<m1->height; i++)
    {
        for(size_t j = 0; j<m1->width; j++)
        {
            m1->data[i*m1->width+j]+=m2->data[i*m1->width+j];
        }
    }
}

void matrix_free(struct matrix *m)
{
    free(m->data);
    free(m);
}
