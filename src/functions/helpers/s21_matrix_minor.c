/**
 * @file s21_matrix_minor.c
 * @brief Вычисление минора матрицы
 */

#include "../../s21_matrix.h"

int s21_matrix_minor(const matrix_t *A, int row, int col, double *result) {
    int status = S21_OK;
    
    // Проверка входных данных
    if (checking_arg(A) != S21_OK || result == NULL) {
        status = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        status = S21_CALC_ERROR;
    } else if (row < 0 || row >= A->rows || col < 0 || col >= A->columns) {
        status = S21_CALC_ERROR;
    } else {
        int n = A->rows;
        
        // Для матрицы 1x1 минор равен единственному элементу
        if (n == 1) {
            *result = A->data[0];
        } else {
            int minor_size = n - 1;
            matrix_t minor = {0};
            
            if (s21_create_matrix(minor_size, minor_size, &minor) != S21_OK) {
                status = S21_INCORRECT_MATRIX;
            } else {
                // Заполнение матрицы минора (удаляем строку row и столбец col)
                int minor_i = 0;
                for (int i = 0; i < n && status == S21_OK; ++i) {
                    // Пропускаем удаляемую строку
                    if (i != row) {
                        int minor_j = 0;
                        for (int j = 0; j < n; ++j) {
                            // Пропускаем удаляемый столбец
                            if (j != col) {
                                minor.data[minor_i * minor_size + minor_j] = A->data[i * n + j];
                                minor_j++;
                            }
                        }
                        minor_i++;
                    }
                }
                
                // Вычисляем определитель минора
                status = s21_determinant(&minor, result);
                s21_remove_matrix(&minor);
            }
        }
    }
    
    return status;
}