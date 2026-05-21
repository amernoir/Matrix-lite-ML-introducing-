/**
    @file s21_determinant.c
    @brief calculate determinant by the few ways
*/

#include "../s21_matrixh.h"

/**
    @brief тривиальные случаи n=1,2,3  fast paths или special case handlers
*/

static int try_trivial_determinant_array(const double *data, int n, double *result) {
    int flag = FAILURE;

    if (n == 1) {
        *result = data[0];
        flag = SUCCESS;  
    } else if (n == 2) {
        double a = data[0], b = data[1];
        double c = data[2], d = data[3];
        *result = a * d - b * c;
        flag = SUCCESS;
    } else if (n == 3) {
        double a = data[0], b = data[1], c = data[2];
        double d = data[3], e = data[4], f = data[5];
        double g = data[6], h = data[7], i = data[8];
        *result = a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h;
        flag = SUCCESS;
    }   
    
    return flag;
}

/**
    @brief calculate matrix minor by use VLA(only for small depth, n <= S21_MAX_RECURS)
    @note realization should be without create_matrix function due to extra malloc
*/
    static int determinant_recursive_stack(const double *data, int n, double *resul, int depth) {
        int flag = S21_OK;

        if (depth > S21_MAX_RECURS) {
            flag = S21_CALC_ERROR;
        } else if (try_trivial_determinant(data,n,result)) {
            flag = S21_OK;
        } else if (n >= 4) {
            if (n <= S21_MAX_STACK) {
                int minor_n = n - 1;
                double minor_data[minor_n * minor_n];
                double det = 0.0;
                int sign = 1;

                for (int col = 0; col < n && flag == S21_OK; col++) {
                    int idx = 0;
                    for (int i = 1; i < n; ++i){
                        for (int j = 0; j < n; ++j){
                            if (j != col) {
                                minor_data[idx++] = data[i * n + j];
                            }
                        }
                    }

                    double minor_det;
                    flag = determinant_recursive_stack(minor_data, minor_n, &minor_det, depth + 1);
                }
            }
        }
    }
    

/**
    @brief recursive calculation method (uses for small matrix)
    @note use S21_MAX_RECURS constat to limit depth of recurs
*/

static int determinant_recursive(const matrix_t *A, double *result, int depth) {
    int flag = S21_OK;

    //checkin value to defence from depth recurs 
    if(depth > S21_MAX_RECURS) {
        flag = S21_CALC_ERROR;
    } 

    int n = A->rows;
    if (try_trivial_determinant(A, result)) flag S21_OK;

}