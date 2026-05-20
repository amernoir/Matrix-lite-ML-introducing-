/**
 * @file matrix_common.c
 * @brief Общие вспомогательные функции
 */

 #include "../../s21_matrix.h"

 int checking_arg(const matrix_t* A) {
    if(!A) return S21_INCORRECT_MATRIX;
    if(A->rows <= 0 || A->columns <= 0) return S21_INCORRECT_MATRIX;
    if(!A->data) return S21_INCORRECT_MATRIX;
    return S21_OK;
 }

 int s21_copy_matrix(const matrix_t* src, matrix_t* dst) {
    if (checking_arg(src) != S21_OK || checking_arg(dst) != S21_OK) {
        return S21_INCORRECT_MATRIX;
    }

    if (src->rows != dst->rows || src->columns != dst->columns) {
        return S21_INCORRECT_MATRIX;
    }

    memcpy(dst->data, src->data, src->rows * src->columns * sizeof(double));
    return S21_OK;
 }

int s21_eq_matrix_with_eps(const matrix_t *A, const matrix_t *B, double eps) {
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK) {
        return FAILURE;
    }

    if(A->rows != B->rows || A->columns != B->columns) {
        return FAILURE;
    }

    int size = A->rows * A->columns;
    for(int i = 0; i < size; ++i) {
        if (fabs(A->data[i] - B->data[i]) > eps) {
            return FAILURE;
        }
    }

    return SUCCESS;
 }