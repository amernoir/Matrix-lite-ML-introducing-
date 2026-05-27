#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    // s21_remove_matrix(result); попытка очистки мусора - сигфолт
    result->rows = 0;
    result->columns = 0;
    result->data = NULL;
    
    result->data = (double *)calloc(rows * columns, sizeof(double));

    if (result->data == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    result->rows = rows;
    result->columns = columns;

    return S21_OK;
}