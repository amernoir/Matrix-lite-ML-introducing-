/**
 * @file s21_mult_matrix.c
 * @brief Умножение двух матриц
 */

#include "../s21_matrix.h"

int s21_mult_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int flag = S21_OK;
    
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->columns != B->rows) {
        flag = S21_CALC_ERROR;
    } else {
        // Создаём новую матрицу (result должен быть неинициализирован)
        if (s21_create_matrix(A->rows, B->columns, result) != S21_OK) {
            flag = S21_INCORRECT_MATRIX;
        } else {
            int a_rows = A->rows;
            int a_cols = A->columns;
            int b_cols = B->columns;
            
            for (int i = 0; i < a_rows; ++i) {
                for (int j = 0; j < b_cols; ++j) {
                    double sum = 0.0;
                    for (int k = 0; k < a_cols; ++k) {
                        sum += A->data[i * a_cols + k] * B->data[k * b_cols + j];
                    }
                    result->data[i * b_cols + j] = sum;
                }
            }
        }
    }
    
    return flag;
}