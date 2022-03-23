#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

struct matrix
{
    size_t data_size;
    size_t width;
    size_t height;
    double *data;
};

/**
** Create a matrix of int
*/
struct matrix* matrix_new(size_t width, size_t height);

/**
** Sum the value of the n-th column
*/
double matrix_col_sum(struct matrix *m, size_t n);

/**
** Sum the value of the n-th row
*/
double matrix_row_sum(struct matrix *m, size_t n);

/**
**  Increments the elem at the i col and j row by val
*/
void matrix_add_at(struct matrix *m, size_t i, size_t j,double val);

/**
** Multiply the matrix by scalar
*/
void matrix_scalar_mult(struct matrix *m, int scalar);

/**
** Return a matrix of m1*m2 (in that order)
** Return NULL if m1->width != m2->height
*/
struct matrix *matrix_mult(struct matrix *m1, struct matrix *m2);

/**
** m1 += m2
*/
void matrix_sum(struct matrix *m1, struct matrix *m2);

#endif /* ! MATRIX_H */
