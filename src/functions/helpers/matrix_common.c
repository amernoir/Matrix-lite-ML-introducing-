/**
 * @file matrix_common.c
 * @brief Общие вспомогательные функции
 */

#include "../../s21_matrix.h"

int checking_arg(const matrix_t* A) {
    int flag = S21_OK;
    
    if (!A) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->rows <= 0 || A->columns <= 0) {
        flag = S21_INCORRECT_MATRIX;
    } else if (!A->data) {
        flag = S21_INCORRECT_MATRIX;
    }
    
    return flag;
}

int s21_copy_matrix(const matrix_t* src, matrix_t* dst) {
    int flag = S21_OK;
    
    if (checking_arg(src) != S21_OK || checking_arg(dst) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else if (src->rows != dst->rows || src->columns != dst->columns) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        memcpy(dst->data, src->data, src->rows * src->columns * sizeof(double));
    }
    
    return flag;
}

int s21_eq_matrix_with_eps(const matrix_t *A, const matrix_t *B, double eps) {
    int flag = SUCCESS;
    
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK) {
        flag = FAILURE;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        flag = FAILURE;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size && flag == SUCCESS; ++i) {
            double diff = fabs(A->data[i] - B->data[i]);
            double rel_diff = fabs(A->data[i] - B->data[i]);
            double max_val = fmax(fabs(A->data[i]), fabs(B->data[i]));
            
            if (diff > S21_EPS_ABS && rel_diff > S21_EPS_REL * max_val) {
                flag = FAILURE;
            }
        }
    }
    
    return flag;
}

int two_matrix_create(const int a_rows, const int a_cols, matrix_t *A,
                      const int b_rows, const int b_cols, matrix_t *B) {
    int flag = S21_OK;
    
    if (A == NULL || B == NULL) {
        flag = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(a_rows, a_cols, A) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(b_rows, b_cols, B) != S21_OK) {
        s21_remove_matrix(A);
        flag = S21_INCORRECT_MATRIX;
    }
    
    return flag;
}

void s21_fill_matrix(matrix_t *A, double value) {
    if (A != NULL && A->data != NULL) {
        int size = A->rows * A->columns;
        for (int i = 0; i < size; ++i) {
            A->data[i] = value;
        }
    }
}

void s21_zero_matrix(matrix_t *A) {
    s21_fill_matrix(A, 0.0);
}