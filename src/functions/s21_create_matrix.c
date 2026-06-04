/**
    @file s21_create_matrix.c
    @brief create new matrix
*/

#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    if (result->data != NULL) {
        s21_remove_matrix(result);
    }

    result->data = (double *)calloc(rows * columns, sizeof(double));
    if (result->data == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    result->rows = rows;
    result->columns = columns;
    return S21_OK;
}