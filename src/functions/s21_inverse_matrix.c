 /**
 * @file s21_inverse_matrix.c
 * @brief Обратная матрица
 */

 #include "../s21_matrix.h"

int s21_inverse_matrix(const matrix_t *A, matrix_t *result) {
    int status = S21_OK;

    if(checking_arg(A) != S21_OK || result == NULL) {
        status = S21_INCORRECT_MATRIX;
    } else if (A->rows != A->columns) {
        status = S21_CALC_ERROR;
    } else {
        double det = 0;
        status = s21_determinant(A, &det);

        if (status != S21_OK || fabs(det) < S21_EPS) {
            status = S21_CALC_ERROR;
        } else {
            if (A->rows == 1) {
                if(s21_create_matrix(1,1,result) != S21_OK) {
                    status = S21_INCORRECT_MATRIX;
                } else {
                    result->data[0] = 1.0 / det;
                }
            } else {
                matrix_t complements = {0};
                status = s21_calc_complements(A, &complements);

                if (status == S21_OK){
                    matrix_t adjugate = {0};
                    status = s21_transpose(&complements,&adjugate);
                    s21_remove_matrix(&complements);

                    if (status == S21_OK) {
                        status = s21_mult_number(&adjugate, 1.0 / det, result);
                        s21_remove_matrix(&adjugate);
                    }
                }
            }
        }
    }
    return status;
}