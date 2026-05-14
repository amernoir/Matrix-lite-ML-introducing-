/**
 * @file s21_sum_matrix.c
 * @brief Реализация функции сравнения матриц
*/

#include "../s21_matrix.h"
int s21_sum_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result){
    if (A == NULL || B == NULL || 
        A->data == NULL || B->data == NULL) {
            return S21_INCORRECT_MATRIX;
        }
}