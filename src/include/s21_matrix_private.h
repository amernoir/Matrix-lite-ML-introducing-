/**
* @file s21_matrix_private.h
* @brief ВНУТРЕННИЕ функции библиотеки, не для пользования пользователем 
* @details header file для вспомогательных функций, предназначенных 
* для реализации матричных операций
* @author fairyjac   
*/

#ifndef S21_MATRIX_PRIVATE_H
#define S21_MATRIX_PRIVATE_H

#include "s21_matrix_types.h"
#include "s21_matrix_aliases.h"

// ==================== ПРОВЕРКИ ====================

/**
* @brief проверка на корректность матрицы
* @param A указатель на матрицу
* @return S21_OK - корректна, S21_INCORRECT_MATRIX - некорректна
*/
int checking_arg(const matrix_t *A);

// ==================== ОПЕРАЦИИ С МАТРИЦАМИ ====================

/**
 * @brief Применение бинарной операции к элементам двух матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @param result результат операции
 * @param op указатель на функцию операции (a, b) -> значение
 * @return S21_OK, S21_INCORRECT_MATRIX, S21_CALC_ERROR
 */
int matrix_apply_binary(const matrix_t *A, const matrix_t *B,
                        matrix_t *result, double (*op)(double, double));

/**
 * @brief Применение унарной операции к элементам матрицы
 * @param A исходная матрица
 * @param result результат операции
 * @param op указатель на функцию операции (a) -> значение
 * @return S21_OK, S21_INCORRECT_MATRIX
 */
int matrix_apply_unary(const matrix_t *A, matrix_t *result,
                       double (*op)(double));

/**
 * @brief Применение унарной операции с параметром
 * @param A исходная матрица
 * @param result результат операции
 * @param op указатель на функцию операции (a, param) -> значение
 * @param param параметр операции
 * @return S21_OK, S21_INCORRECT_MATRIX
 */
int matrix_apply_unary_with_param(const matrix_t *A, matrix_t *result,
                                  double (*op)(double, double), double param);

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================

/**
 * @brief Создание двух матриц с откатом при ошибке
 * @param a_rows, a_cols размеры матрицы A
 * @param A указатель на первую матрицу
 * @param b_rows, b_cols размеры матрицы B
 * @param B указатель на вторую матрицу
 * @return S21_OK - успех, иначе ошибка (с очисткой)
 */
int two_matrix_create(int a_rows, int a_cols, matrix_t *A,
                      int b_rows, int b_cols, matrix_t *B);

/**
 * @brief Копирование матрицы (dst уже должна быть создана)
 * @param src исходная матрица
 * @param dst целевая матрица
 * @return S21_OK, S21_INCORRECT_MATRIX
 */
int s21_copy_matrix(const matrix_t *src, matrix_t *dst);

/**
 * @brief Заполнение всех элементов матрицы значением
 * @param A матрица
 * @param value значение
 */
void s21_fill_matrix(matrix_t *A, double value);

/**
 * @brief Обнуление всех элементов матрицы
 * @param A матрица
 */
void s21_zero_matrix(matrix_t *A);

// ==================== ВНУТРЕННИЕ ФУНКЦИИ ДЛЯ ОПРЕДЕЛИТЕЛЯ ====================

/**
 * @brief Рекурсивное вычисление определителя (только для n <= S21_MAX_RECURS)
 * @param data указатель на данные матрицы (row-major)
 * @param n размер матрицы
 * @param result указатель на результат
 * @return S21_OK, S21_CALC_ERROR
 */
int determinant_recursive_stack(const double *data, int n, double *result);

/**
 * @brief Рекурсивное вычисление определителя с динамической памятью
 * @param data указатель на данные матрицы (row-major)
 * @param n размер матрицы
 * @param result указатель на результат
 * @return S21_OK, S21_CALC_ERROR
 */
int determinant_recursive_dynamic(const double *data, int n, double *result);

/**
 * @brief Вычисление определителя методом LU-разложения (для больших матриц)
 * @param A исходная матрица
 * @param result указатель на результат
 * @return S21_OK, S21_CALC_ERROR
 */
int determinant_lu(const matrix_t *A, double *result);

#endif // S21_MATRIX_PRIVATE_H

/**
 * @brief Вычисление минора матрицы (определитель подматрицы)
 * @param A исходная квадратная матрица
 * @param row строка для удаления
 * @param col столбец для удаления
 * @param result указатель на результат (определитель минора)
 * @return S21_OK - успех, S21_INCORRECT_MATRIX - ошибка, S21_CALC_ERROR - ошибка вычисления
 */
int s21_matrix_minor(const matrix_t *A, int row, int col, double *result);