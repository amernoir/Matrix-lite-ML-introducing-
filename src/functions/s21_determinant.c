/**
    @file s21_determinant.c
    @brief calculate determinant by the few ways
*/


#include "../s21_matrix.h"

static int determinant_recursive_dynamic(const double *data, int n, double *result);
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
    @brief calculate matrix minor by use VLA(only for small depth, n <= S21_MAX_STACK)
    @note realization should be without create_matrix function due to extra malloc
*/
static int determinant_recursive_stack(const double *data, int n, double *result) {
    int flag = S21_OK;

    if (try_trivial_determinant_array(data,n,result)) {
        flag = S21_OK;
    } else {     
            int minor_n = n - 1;
            double minor_data[minor_n * minor_n];
            double det = 0.0;
            int sign = 1;
           
            for (int col = 0; col < n && flag == S21_OK; col++) {
                int idx = 0;
                for (int i = 1; i < n; ++i){                        for (int j = 0; j < n; ++j){
                        if (j != col) {
                            minor_data[idx++] = data[i * n + j];
                        }
                    }
                }

                double minor_det;
                flag = determinant_recursive_stack(minor_data, minor_n, &minor_det);
               
                if (flag == S21_OK) {
                    det += sign * data[col] * minor_det;
                    sign = -sign;
                }
            }

            if (flag == S21_OK) {
                *result = det;
            }
    }
    return flag;
}
        
    
/**
    @brief recursive calculation method (uses for small matrix)
    @note use S21_MAX_RECURS constat to limit depth of recurs
*/

static int determinant_recursive_dynamic(const double  *data, int n, double *result) {
    int flag = S21_OK;

    if (try_trivial_determinant_array(data, n, result)) {

    }
    else {

        int minor_n = n - 1;
        int minor_size = minor_n * minor_n;
        double *minor_data = (double*)malloc(minor_size * sizeof(double));

        if (minor_data == NULL) {
            flag = S21_INCORRECT_MATRIX;
        } else {
            double det = 0.0;
            int sign = 1;

            for (int col = 0; col < n && flag == S21_OK; col++) {
                int idx = 0;
                for (int i = 1; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (j != col) {
                            minor_data[idx++] = data[i * n + j];
                        }
                    }
                }

                double minor_det;
                flag = determinant_recursive_dynamic(minor_data, minor_n, &minor_det);

                if (flag == S21_OK) {
                    det += sign * data[col] * minor_det;
                    sign = -sign;
                }
            }

            if (flag == S21_OK) {
                *result = det;
            }

            free(minor_data);
        }
    }
    return flag;
}

/**
    @brief det calculate by Gaussian (triangle method)

*/

static int determinant_gaussian(const matrix_t *A, double *result) {
    int n = A->rows; 
    int flag = S21_OK;

    matrix_t temp = {0};
    if (s21_create_matrix(n, n, &temp) != S21_OK) {
        flag = S21_INCORRECT_MATRIX;
    }

    for (int i = 0; i < n * n; ++i) {
        temp.data[i] = A->data[i];
    }

    double det = 1.0;
    int swap_count = 0;

    for (int k = 0; k < n; k++) {
        int max_row = k;
        double max_val = fabs(temp.data[k * n + k]);

        for (int i = k + 1; i < n; ++i) {
            double val = fabs(temp.data[i * n + k]);
            if (val > max_val) {
                max_val = val;
                max_row = i;
            }
        }
        // вырожденная матрица 
        if (max_val < S21_EPS_ABS) {
            *result = 0.0;
            s21_remove_matrix(&temp);
            flag = S21_OK;
        }

        if (max_row != k) {
            swap_count++;
            for (int j = 0; j < n; ++j) {
                double tmp = temp.data[k * n + j];
                temp.data[k * n + j] = temp.data[max_row * n + j];
                temp.data[max_row * n + j] = tmp;
            }
        }

        
    }
}