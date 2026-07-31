/**
 * @file s21_eq_matrix.c
 * @brief Сравнение матриц
 */

#include "s21_matrix.h"

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
    return s21_eq_matrix_with_eps(A, B, S21_EPS);
}
