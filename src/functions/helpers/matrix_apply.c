/**
 * @file matrix_apply.c
 * @brief применение операций к матрицам, использование паттерна стратегия 
*/

#include "../../s21_matrix.h"

int matrix_apply_binary(const matrix_t *A, const matrix_t *B,
                        matrix_t *result, binary_op_t op, double param) {
      if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }

        if (A->rows != B->rows || A->columns != B->columns) {
            return S21_CALC_ERROR;
        }

        if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
            return S21_CALC_ERROR;
        }

        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            result->data[i] = op(A->data[i], B->data[i], param);
        }

        return S21_OK;
}

int matrix_apply_unary (const matrix_t *A, matrix_t *result,
                        unary_op_t op, double param) {
    
     if (checking_arg(A) != S21_OK || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }                   

    if (s21_create_matrix(A->rows, A->columns, result) != S21_OK) {
        return S21_INCORRECT_MATRIX;
    }

    int size = A->rows * A->columns;
    for(int i = 0; i < size; ++i) {
        result->data[i] = op(A->data[i], param);
    }

    return S21_OK;
}

int s21_mult_matrix_basic(const matrix_t *A, const matrix_t *B, matrix_t *result) {
      if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }


    if (A->columns != B->rows) {
        return S21_CALC_ERROR;
    }

    if(result->data != NULL){
        s21_remove_matrix(result);
    }

    if (s21_create_matrix(A->rows, B->columns, result) != S21_OK) {
        result->data = NULL;
        return S21_INCORRECT_MATRIX;
    }

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

    return S21_OK;
}