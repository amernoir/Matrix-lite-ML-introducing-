/**
 * @file s21_blas.c
 * @brief Реализация BLAS-оптимизированных функций для матричных операций
 * @note Использует OpenBLAS/cblas для ускорения вычислений
 */

#include "s21_matrix.h"
#include "include/s21_blas.h"
#include <cblas.h>

// Глобальный флаг инициализации BLAS
static int blas_initialized = 0;

int s21_blas_init(void) {
    // Для OpenBLAS инициализация не требуется, но оставляем для совместимости
    blas_initialized = 1;
    return S21_OK;
}

void s21_blas_cleanup(void) {
    blas_initialized = 0;
}

int s21_blas_available(void) {
    // Всегда возвращаем 1, так как cblas доступен после линковки
    return 1;
}

/**
 * @brief Сложение матриц с использованием BLAS (DAXPY для каждой строки)
 */
int s21_sum_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    if (!A || !B || !result || !A->data || !B->data || !result->data) {
        return S21_INCORRECT_MATRIX;
    }
    
    if (A->rows != B->rows || A->columns != B->columns ||
        A->rows != result->rows || A->columns != result->columns) {
        return S21_INCORRECT_MATRIX;
    }
    
    int size = A->rows * A->columns;
    
    // Копируем A в result
    memcpy(result->data, A->data, size * sizeof(double));
    
    // result = result + 1.0 * B
    cblas_daxpy(size, 1.0, B->data, 1, result->data, 1);
    
    return S21_OK;
}

/**
 * @brief Вычитание матриц с использованием BLAS
 */
int s21_sub_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    if (!A || !B || !result || !A->data || !B->data || !result->data) {
        return S21_INCORRECT_MATRIX;
    }
    
    if (A->rows != B->rows || A->columns != B->columns ||
        A->rows != result->rows || A->columns != result->columns) {
        return S21_INCORRECT_MATRIX;
    }
    
    int size = A->rows * A->columns;
    
    // Копируем A в result
    memcpy(result->data, A->data, size * sizeof(double));
    
    // result = result - 1.0 * B
    cblas_daxpy(size, -1.0, B->data, 1, result->data, 1);
    
    return S21_OK;
}

/**
 * @brief Умножение матрицы на число с использованием BLAS (DSCAL)
 */
int s21_mult_number_blas(const matrix_t *A, double number, matrix_t *result) {
    if (!A || !result || !A->data || !result->data) {
        return S21_INCORRECT_MATRIX;
    }
    
    if (A->rows != result->rows || A->columns != result->columns) {
        return S21_INCORRECT_MATRIX;
    }
    
    int size = A->rows * A->columns;
    
    // Копируем A в result
    memcpy(result->data, A->data, size * sizeof(double));
    
    // result = number * result
    cblas_dscal(size, number, result->data, 1);
    
    return S21_OK;
}

/**
 * @brief Умножение матриц с использованием BLAS GEMM
 * C = alpha * op(A) * op(B) + beta * C
 */
int s21_mult_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    if (!A || !B || !result || !A->data || !B->data || !result->data) {
        return S21_INCORRECT_MATRIX;
    }
    
    if (A->columns != B->rows) {
        return S21_CALC_ERROR;
    }
    
    if (result->rows != A->rows || result->columns != B->columns) {
        return S21_INCORRECT_MATRIX;
    }
    
    int M = A->rows;      // строки A
    int K = A->columns;   // колонки A = строки B
    int N = B->columns;   // колонки B
    
    // C = A * B (без транпонирования, alpha=1.0, beta=0.0)
    // Row-major: используем CblasRowMajor
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                M, N, K,
                1.0,
                A->data, K,
                B->data, N,
                0.0,
                result->data, N);
    
    return S21_OK;
}

/**
 * @brief Автоматический выбор между BLAS и стандартной реализацией
 */
int s21_sum_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int size = (A && A->rows > 0 && A->columns > 0) ? A->rows * A->columns : 0;
    
    // Для маленьких матриц используем стандартную реализацию (меньше overhead)
    if (size < S21_BLAS_THRESHOLD * S21_BLAS_THRESHOLD || !s21_blas_available()) {
        return s21_sum_matrix(A, B, result);
    } else {
        return s21_sum_matrix_blas(A, B, result);
    }
}

int s21_sub_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int size = (A && A->rows > 0 && A->columns > 0) ? A->rows * A->columns : 0;
    
    if (size < S21_BLAS_THRESHOLD * S21_BLAS_THRESHOLD || !s21_blas_available()) {
        return s21_sub_matrix(A, B, result);
    } else {
        return s21_sub_matrix_blas(A, B, result);
    }
}

int s21_mult_number_auto(const matrix_t *A, double number, matrix_t *result) {
    int size = (A && A->rows > 0 && A->columns > 0) ? A->rows * A->columns : 0;
    
    if (size < S21_BLAS_THRESHOLD * S21_BLAS_THRESHOLD || !s21_blas_available()) {
        return s21_mult_number(A, number, result);
    } else {
        return s21_mult_number_blas(A, number, result);
    }
}

int s21_mult_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result) {
    int size_a = (A && A->rows > 0 && A->columns > 0) ? A->rows * A->columns : 0;
    int size_b = (B && B->rows > 0 && B->columns > 0) ? B->rows * B->columns : 0;
    int total_size = (size_a > size_b) ? size_a : size_b;
    
    if (total_size < S21_BLAS_THRESHOLD * S21_BLAS_THRESHOLD || !s21_blas_available()) {
        return s21_mult_matrix(A, B, result);
    } else {
        return s21_mult_matrix_blas(A, B, result);
    }
}
