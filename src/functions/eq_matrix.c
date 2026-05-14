/**
 * @file eq_matrix.c
 * @brief Реализация функции сравнения матриц
 */

#include "../s21_matrix.h"

int s21_eq_matrix(const matrix_t *A, const matrix_t *B){
    if (A == NULL || B == NULL || 
        A->data == NULL || B->data == NULL ||
        A->rows != B->rows || A->columns != B->columns) {
            return FAILURE;
    }

    if (A == B) return SUCCESS;

    int size = A->rows * A->columns;
    for (int i = 0; i < size; ++i) {
        if (fabs(A->data[i] - B->data[i]) > S21_EPS_ABS) {
            return FAILURE;
        }

    }
    return SUCCESS;
}