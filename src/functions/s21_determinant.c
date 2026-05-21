/**
    @file s21_determinant.c
    @brief calculate determinant by the few ways
*/

#include "../s21_matrixh.h"

/**
    @brief тривиальные случаи n=1,2,3
*/

static int try_trivial_determinant(const matrix_t *A, double *result) {
    int n = A->rows;
    int flag = S21_OK;

    if (n == 1) {
        *result = A->data[0];
        flag = S    
    }
}