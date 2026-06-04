/**
 * @file eq_matrix.c
 * @brief equal function
 */

#include "../s21_matrix.h"

int s21_eq_matrix(const matrix_t *A, const matrix_t *B){
    int flag = SUCCESS;
    
    if (checking_arg(A) != S21_OK || checking_arg(B) != S21_OK) {
        flag = FAILURE;
    } else if (A->rows != B->rows || A->columns != B->columns) {
        flag = FAILURE;
    } else if (A == B) {
        flag = SUCCESS;
    } else {
        int size = A->rows * A->columns;
        for (int i = 0; i < size && flag == SUCCESS; ++i) {
            if (fabs(A->data[i] - B->data[i]) > S21_EPS_ABS) {
                flag = FAILURE;
            }
        }
    }
    
    return flag;
}