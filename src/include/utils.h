/**
* @file utils.h
* @brief макросы и утилиты для matrix library
* @author fairyjac
*/

#ifndef UTILS_H
#define UTILS_H

#include <math.h>

// Forward declaration
typedef struct matrix {
    double *data;
    int rows;
    int columns;
} matrix_t;

// ==================== БАЗОВЫЕ ОПЕРАЦИИ ДЛЯ APPLY ====================

// Бинарные операции (матрица + матрица)
static inline double add_op(double a, double b) { return a + b; }
static inline double sub_op(double a, double b) { return a - b; }
static inline double mul_op(double a, double b) { return a * b; }

// Унарные операции с параметром (матрица * число, матрица + число)
static inline double scale_op(double a, double param) { return a * param; }
static inline double add_scalar_op(double a, double param) { return a + param; }

// ==================== ВСПОМОГАТЕЛЬНЫЕ МАКРОСЫ ====================

/**
 * @brief Безопасная очистка двух матриц
 * @param a первая матрица (указатель)
 * @param b вторая матрица (указатель)
 */
#define S21_CLEANUP_MATRICES(a, b)              \
    do {                                        \
        if (a != NULL && (a)->data != NULL)     \
            s21_remove_matrix(a);               \
        if (b != NULL && (b)->data != NULL)     \
            s21_remove_matrix(b);               \
    } while (0)

/**
 * @brief Доступ к элементу матрицы (row-major)
 */
#define S21_MATRIX_ELEM(m, i, j) ((m)->data[(i) * (m)->columns + (j)])

#endif // UTILS_H
