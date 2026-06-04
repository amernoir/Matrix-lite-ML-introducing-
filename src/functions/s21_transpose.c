/**
    @file s21_transpose.c
    @brief транспонирование матрицы - линейная операция 
    @note A^T - есть матрицца в которой строки и стобцы поменяны местами
*/

#include "../s21_matrix.h"

int s21_transpose(const matrix_t *A, matrix_t *result) {
    int status = S21_OK;

    if(checking_arg(A) != S21_OK || result == NULL){
        status = S21_INCORRECT_MATRIX;
    } else if (s21_create_matrix(A->columns, A->rows, result) != S21_OK) {
        status = S21_INCORRECT_MATRIX;
    } else {
        for (int i = 0; i < A->rows && status == S21_OK; ++i) {
            for (int j = 0; j < A->columns; ++j) {
                result->data[j * A->rows + i] = A->data[i * A->columns + j];
            }
        }
    }

    return status;
}