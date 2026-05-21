/**
 * @file matrix_apply.c
 * @brief применение операций к матрицам, использование паттерна стратегия 
 */

#include "../../s21_matrix.h"

int matrix_apply_binary(const matrix_t *A, const matrix_t *B,
                        matrix_t *result, binary_op_t op, double param) {
    int flag = S21_OK;
    
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        flag = S21_CALC_ERROR;
    } else if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        flag = S21_CALC_ERROR;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            result->data[i] = op(A->data[i], B->data[i], param);
        }
    }
    
    return flag;
}

int matrix_apply_unary(const matrix_t *A, matrix_t *result,
                       unary_op_t op, double param) {
    int flag = S21_OK;
    
    if (checking_arg(A) != S21_OK || result == NULL) {
        flag = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            result->data[i] = op(A->data[i], param);
        }
    }
    
    return flag;
}

int s21_mult_matrix_basic(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int flag = S21_OK;
    
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->columns != B->rows) {
        flag = S21_CALC_ERROR;
    } else {
        if (result->data != NULL) {
            s21_remove_matrix(result);
        }
        
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