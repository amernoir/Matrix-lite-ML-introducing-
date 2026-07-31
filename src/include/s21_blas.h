/**
 * @file s21_blas.h
 * @brief BLAS-оптимизированные функции для матричных операций
 * @note Использует cblas для ускорения вычислений на больших матрицах
 */

#ifndef S21_BLAS_H
#define S21_BLAS_H

#include "s21_matrix.h"

// Порог для использования BLAS (для маленьких матриц overhead слишком большой)
#define S21_BLAS_THRESHOLD 32

/**
 * @brief Инициализация BLAS (если требуется)
 * @return 0 - успех, 1 - ошибка
 */
int s21_blas_init(void);

/**
 * @brief Очистка ресурсов BLAS
 */
void s21_blas_cleanup(void);

/**
 * @brief Проверка доступности BLAS
 * @return 1 - доступен, 0 - недоступен
 */
int s21_blas_available(void);

/**
 * @brief Оптимизированное сложение матриц с использованием BLAS
 * @param A - первая матрица
 * @param B - вторая матрица  
 * @param result - результат (A + B)
 * @return 0 - ok, 1 - error
 */
int s21_sum_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Оптимизированное вычитание матриц с использованием BLAS
 * @param A - уменьшаемое
 * @param B - вычитаемое
 * @param result - результат (A - B)
 * @return 0 - ok, 1 - error
 */
int s21_sub_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Оптимизированное умножение матрицы на число с использованием BLAS
 * @param A - исходная матрица
 * @param number - множитель
 * @param result - результат
 * @return 0 - ok, 1 - error
 */
int s21_mult_number_blas(const matrix_t *A, double number, matrix_t *result);

/**
 * @brief Оптимизированное умножение матриц с использованием BLAS (GEMM)
 * @param A - первая матрица (M x K)
 * @param B - вторая матрица (K x N)
 * @param result - результат (M x N)
 * @return 0 - ok, 1 - error
 */
int s21_mult_matrix_blas(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Универсальная функция сложения (автоматически выбирает BLAS или стандартную)
 * @param A - первая матрица
 * @param B - вторая матрица
 * @param result - результат
 * @return 0 - ok, 1 - error
 */
int s21_sum_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Универсальная функция вычитания (автоматически выбирает BLAS или стандартную)
 */
int s21_sub_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Универсальная функция умножения на число (автоматически выбирает BLAS или стандартную)
 */
int s21_mult_number_auto(const matrix_t *A, double number, matrix_t *result);

/**
 * @brief Универсальная функция умножения матриц (автоматически выбирает BLAS или стандартную)
 */
int s21_mult_matrix_auto(const matrix_t *A, const matrix_t *B, matrix_t *result);

#endif // S21_BLAS_H
