/**
 * @file s21_create_matrix.c
 * @brief Создание матрицы
 */

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int flag = S21_OK;

    if (!result || rows <= 0 || columns <= 0) {
        flag = S21_INCORRECT_MATRIX;
    } else {
        result->rows = rows;
        result->columns = columns;
        result->data = (double *)calloc(rows * columns, sizeof(double));
        
        if (!result->data) {
            result->rows = 0;
            result->columns = 0;
            flag = S21_INCORRECT_MATRIX;
        }
    }

    return flag;
}
