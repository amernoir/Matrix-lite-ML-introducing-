/**
    @file matrix_minor.c
    @brief minor operations 
*/

#include "../../s21_matrix.h"

void matrix_fill_minor_buffer(const matrix_t *A, int n, int row, int col,
                              double *buf, int buf_offset) {
    int buf_idx = buf_offset;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != row && j != col) {
                buf[buf_idx++] = A->data[i * n + j];
            }
        }
    }
}

int matrix_minor(const matrix_t *A, int row, int col, double *result) {
    int flag = S21_OK;

    if(checking_arg(A) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        flag = S21_CALC_ERROR;
    } else if (row < 0 || row >= A->rows || col < 0 || col >= A->columns) {
        flag = S21_CALC_ERROR;
    } else {
        int n = A->rows;

        if(n == 1){
            *result = A->data[0];
        } else {
            int minor_size = (n - 1) * (n - 1); // count of elements, for example 3x3 = 9 elem
            double *minor_data = (double *)malloc(minor_size * sizeof(double));

            if(minor_data == NULL) {
                flag = S21_INCORRECT_MATRIX;
            } else {
                matrix_fill_minor_buffer(A, n, row, col, minor_data, 0);

                matrix_t minor = {0};
                minor.data = minor_data;
                minor.rows = n - 1;
                minor.columns = n - 1;

                flag = determinant_recursive(&minor, result, n - 1, 0, 0, NULL, 0);

                free(minor_data);
            }
        }
    }

    return flag;
}