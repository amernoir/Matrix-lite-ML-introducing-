/**
 * @file s21_transpose.c
 * @brief Транспонирование матрицы
 */

#include "s21_matrix.h"

int s21_transpose(const matrix_t *A, matrix_t *result) {
    int flag = S21_OK;

    if (checking_arg(A) != S21_OK || !result) {
        flag = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(A->columns, A->rows, result) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->data[j * A->rows + i] = A->data[i * A->columns + j];
            }
        }
    }

    return flag;
}
