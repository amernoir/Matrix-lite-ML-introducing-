/**
 * @file s21_remove_matrix.c
 * @brief Очистка матрицы
 */

#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
    if (A) {
        if (A->data) {
            free(A->data);
            A->data = NULL;
        }
        A->rows = 0;
        A->columns = 0;
    }
}
