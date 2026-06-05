/**
    @file s21_sum_matrix.c
    @brief op +
*/

#include "../s21_matrix.h"

int s21_sum_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result){
    int status = S21_OK;

    if(checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        status = S21_INCORRECT_MATRIX;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        status = S21_CALC_ERROR;
    } else if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        status = S21_INCORRECT_MATRIX;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            result->data[i] = A->data[i] + B->data[i];
        }
    }
    return status;
}