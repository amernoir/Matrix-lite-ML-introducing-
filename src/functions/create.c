/**
 * @file s21_create.c
 * @brief Реализация функции создания матрицы
 */

 #include "../s21_matrix.h"

 int s21_create_matrix(int rows, int columns, matrix_t *result) {
    if (rows <= 0 || columns <= 0 || result == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    s21_remove_matrix(result);

    result->data = (double *)calloc(rows * columns, sizeof(double)); // calloc обнуляет случайные числа, malloc хранит мусор

    if (result->data == NULL) {
        return S21_INCORRECT_MATRIX;
    }

    result->rows = rows;
    result->columns = columns;

    return S21_OK;
}