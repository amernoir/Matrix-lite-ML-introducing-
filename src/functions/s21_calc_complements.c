/**
 * @file s21_calc_complements.c
 * @brief Матрица алгебраических дополнений
 */

#include "s21_matrix.h"

static int calc_minor(const matrix_t *A, int row, int col, matrix_t *minor) {
    int n = A->rows;
    int minor_n = n - 1;
    
    if (s21_create_matrix(minor_n, minor_n, minor) != S21_OK) {
        return S21_INCORRECT_MATRIX;
    }
    
    for (int i = 0, mi = 0; i < n; i++) {
        if (i == row) continue;
        for (int j = 0, mj = 0; j < n; j++) {
            if (j == col) continue;
            minor->data[mi * minor_n + mj] = A->data[i * n + j];
            mj++;
        }
        mi++;
    }
    
    return S21_OK;
}

int s21_calc_complements(const matrix_t *A, matrix_t *result) {
    int flag = S21_OK;

    if (checking_arg(A) != S21_OK || !result) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        flag = S21_CALC_ERROR;
    } else if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        int n = A->rows;
        
        if (n == 1) {
            result->data[0] = 1.0;
        } else {
            matrix_t minor = {0};
            
            for (int i = 0; i < n && flag == S21_OK; i++) {
                for (int j = 0; j < n && flag == S21_OK; j++) {
                    if (calc_minor(A, i, j, &minor) != S21_OK) {
                        flag = S21_INCORRECT_MATRIX;
                        break;
                    }
                    
                    double det;
                    if (s21_determinant(&minor, &det) != S21_OK) {
                        flag = S21_CALC_ERROR;
                    } else {
                        // Алгебраическое дополнение: (-1)^(i+j) * M_ij
                        int sign = ((i + j) % 2 == 0) ? 1 : -1;
                        result->data[i * n + j] = sign * det;
                    }
                    
                    s21_remove_matrix(&minor);
                }
            }
        }
    }

    return flag;
}
