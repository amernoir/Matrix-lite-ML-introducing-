/**
 * @file s21_calc_complements.c
 * @brief Вычисление матрицы алгебраических дополнений
 */

#include "../s21_matrix.h"

int s21_calc_complements(const matrix_t *A, matrix_t *result) {
    int status = S21_OK;
    
    if (checking_arg(A) != S21_OK || result == NULL) {
        status = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        status = S21_CALC_ERROR;
    } else {
        int n = A->rows;
        
        if (s21_create_matrix(n, n, result) != S21_OK) {
            status = S21_INCORRECT_MATRIX;
        } else if (n == 1) {
            result->data[0] = 1.0;
        } else {
            for (int i = 0; i < n && status == S21_OK; ++i) {
                for (int j = 0; j < n && status == S21_OK; ++j) {
                    double minor_det = 0;
                    
                    status = s21_matrix_minor(A, i, j, &minor_det);
                    
                    if (status == S21_OK) {
                        // Алгебраическое дополнение: (-1)^(i+j) * det(minor)
                        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
                        result->data[i * n + j] = sign * minor_det;
                    } else {
                        s21_remove_matrix(result);
                    }
                }
            }
        }
    }
    
    return status;
}