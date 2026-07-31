/**
 * @file s21_inverse_matrix.c
 * @brief Обратная матрица
 */

#include "s21_matrix.h"

int s21_inverse_matrix(const matrix_t *A, matrix_t *result) {
    int flag = S21_OK;
    double det = 0.0;

    if (checking_arg(A) != S21_OK || !result) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        flag = S21_CALC_ERROR;
    } else if (s21_determinant(A, &det) != S21_OK || fabs(det) < S21_EPS_ABS) {
        flag = S21_CALC_ERROR;
    } else {
        int n = A->rows;
        
        if (n == 1) {
            if (s21_create_matrix(1, 1, result) != S21_OK) {
                flag = S21_INCORRECT_MATRIX;
            } else {
                result->data[0] = 1.0 / det;
            }
        } else {
            matrix_t complements = {0};
            
            if (s21_calc_complements(A, &complements) != S21_OK) {
                flag = S21_CALC_ERROR;
            } else if (s21_transpose(&complements, result) != S21_OK) {
                flag = S21_INCORRECT_MATRIX;
            } else {
                // Делим на определитель
                double inv_det = 1.0 / det;
                int size = n * n;
                for (int i = 0; i < size; i++) {
                    result->data[i] *= inv_det;
                }
            }
            
            s21_remove_matrix(&complements);
        }
    }

    return flag;
}
