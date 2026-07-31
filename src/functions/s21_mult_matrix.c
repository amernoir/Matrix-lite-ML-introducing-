/**
 * @file s21_mult_matrix.c
 * @brief Умножение матриц
 */

#include "s21_matrix.h"

int s21_mult_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int flag = S21_OK;

    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || !result) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->columns != B->rows) {
        flag = S21_CALC_ERROR;
    } else if (s21_create_matrix(A->rows, B->columns, result) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        s21_zero_matrix(result);
        
        int M = A->rows;
        int K = A->columns;
        int N = B->columns;
        
        // Row-major order умножение: C[i][j] += A[i][k] * B[k][j]
        for (int i = 0; i < M; i++) {
            for (int k = 0; k < K; k++) {
                double a_ik = A->data[i * K + k];
                for (int j = 0; j < N; j++) {
                    result->data[i * N + j] += a_ik * B->data[k * N + j];
                }
            }
        }
    }

    return flag;
}
