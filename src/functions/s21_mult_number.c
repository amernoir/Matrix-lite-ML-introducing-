/**
    @file s21_mult_number.c
    @brief op multiplication
*/

#include "../s21_matrix.h"

int s21_mult_number(const matrix_t *A, double number, matrix_t *result){
    int status = S21_OK;

    if (checking_arg(A) != S21_OK || result == NULL) {
        status = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        status = S21_INCORRECT_MATRIX;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            result->data[i] = A->data[i] * number;
        }
    }

    return status;
}