/**
 * @file s21_remove.c
 * @brief Реализация функции удаления матрицы
 */

 #include "../s21_matrix.h"

 void s21_remove_matrix(matrix_t *A){
    if (A == NULL) return;

    if(A->data != NULL) {
        free(A->data);
        A->data = NULL;
    }

    A->rows = 0;
    A->columns = 0;
 }