/**
 * @file matrix_minor.c
 * @brief minor operations 
 */

#include "../../s21_matrix.h"

int determinant_recursive(const matrix_t *A, double *result, int n,
                          int row, int col, double *buf, int buf_offset) {
    int flag = S21_OK;
    (void)buf;
    (void)buf_offset;

    if(n == 1) {
        *result = A->data[row * A->columns + col];
    } else if (n == 2) {
        double a = A->data[row * A->columns + col];
        double b = A->data[row * A->columns + col + 1];
        double c = A->data[(row + 1) * A->columns + col];
        double d = A->data[(row + 1) * A->columns + col + 1];
        *result = a * d - b * c;
    } else {
        *result = 0.0;
        int sign = 1;
    
        for (int i = 0; i < n && flag == S21_OK; ++i) {
            double minor_det;
            flag = matrix_minor(A, row, col + i, &minor_det);

            if (flag == S21_OK){
                *result += sign * A->data[row * A->columns + col + i] * minor_det;
                sign = -sign;
            }
        }
    }

    return flag;
}