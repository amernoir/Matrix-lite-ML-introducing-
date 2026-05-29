/** 
 * @file s21_matrix.h
 * @brief Function Declarations of the s21_matrix.a Library 
 * @author fairyjac
*/

#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/s21_matrix_aliases.h"
#include "include/s21_matrix_private.h"
#include "include/s21_matrix_types.h"
#include "include/utils.h"

// ==================== БАЗОВЫЕ ФУНКЦИИ ====================

/**
 * @brief создание матрицы 
 * @param rows - строки
 * @param columns - колонки 
 * @param result - указатель на структуру матрицы
 * @return 0 - ok, 1 - error
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
 * @brief очистка матрицы
 * @param A - указатель на матрицу
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @brief сравнение матриц
 * @param A, B - сравниваемые матрицы
 * @return SUCCESS(1) - равны, FAILURE(0) - не равны
 */
int s21_eq_matrix(const matrix_t *A, const matrix_t *B);

// ==================== АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ====================

/**
 * @brief сложение матриц
 * @param A, B - слагаемые
 * @param result - сумма
 * @return 0 - ok, 1 - error, 2 - error with calculation
 */
int s21_sum_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief вычитание матриц
 * @param A - уменьшаемое, B - вычитаемое
 * @param result - разность
 * @return 0 - ok, 1 - error, 2 - error with calculation
 */
int s21_sub_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief умножение матриц
 * @param A, B - множители
 * @param result - произведение
 * @return 0 - ok, 1 - error, 2 - error with calculation
 */
int s21_mult_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief умножение матрицы на число
 * @param A - исходная матрица
 * @param number - множитель
 * @param result - результат
 * @return 0 - ok, 1 - error
 */
int s21_mult_number(const matrix_t *A, double number, matrix_t *result);

// ==================== ОПЕРАЦИИ НАД МАТРИЦАМИ ====================

/**
 * @brief транспонирование матрицы
 * @param A - исходная матрица
 * @param result - транспонированная матрица
 * @return 0 - ok, 1 - error
 */
int s21_transpose(const matrix_t *A, matrix_t *result);

/**
 * @brief вычисление определителя
 * @param A - квадратная матрица
 * @param result - определитель
 * @return 0 - ok, 1 - error, 2 - error (det = 0 или не квадратная)
 */
int s21_determinant(const matrix_t *A, double *result);

/**
 * @brief матрица алгебраических дополнений
 * @param A - квадратная матрица
 * @param result - матрица дополнений
 * @return 0 - ok, 1 - error, 2 - error
 */
int s21_calc_complements(const matrix_t *A, matrix_t *result);

/**
 * @brief обратная матрица
 * @param A - квадратная матрица (det != 0)
 * @param result - обратная матрица
 * @return 0 - ok, 1 - error, 2 - error (det = 0)
 */
int s21_inverse_matrix(const matrix_t *A, matrix_t *result);

#endif // S21_MATRIX_H