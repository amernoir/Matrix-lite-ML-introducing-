/** 
 * @file s21_matrix.h
 * @brief Function Declarations of the s21_matrix.a Library 
 * @details Functions in Task:
 * - s21_create_matrix() >> create 
 * - s21_remove_matrix() >> free resource and destroy object 
 * - s21_eq_matrix() >> compare 
 * - s21_sum_matrix() >> +
 * - s21_sub_matrix() >> -
 * - s21_mult_matrix() >> *
 * - s21_mult_number() >> multiply matrix on digit 
 * - s21_transpose() >> transpose 
 * - s21_determinant() >> определитель 
 * - s21_calc_complements() >> вычисление матрицы алгебраических дополнений
 * - s21_inverse_matrix() >> поиск обратной матрицы
 * @author fairyjac
*/

#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/utils.h"
#include "include/s21_matrix_aliases.h"
#include "include/s21_matrix_private.h"
#include "include/s21_matrix_types.h"

/**
 * @brief создание матриц 
 * @param rows - строки
 * @param columns - колонки 
 * @param result - указатель на ячейку памяти размерностью rows * cols
 * @return - 0 - ok
 * @return - 1 - error, некорреектная матрица
 */

 int s21_create_matrix(int rows, int columns, matrix_t *result);

/**
* @brief очистка матрицы
* @param A - указатель на матрицу
*/

void s21_remove_matrix(matrix_t *A);

/**
* @brief сравнивание матриц
* @param A 
* @param B
* @return - 0, not equal 
* @return - 1, equal 
*/

int s21_eq_matrix(const matrix_t *A, const matrix_t *B);

/**
* - @brief сложение матриц
* - @param A указатель на первое слагаемое 
* - @param B указатель на второе 
* - @param result указатель на вычисленную матрицу
* - @return - 0 - ok
* - @return - 1 - error 
* - @return - 2 - error with calculation 
*/

int s21_sum_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

/**
 * @brief Вычитание двух матриц
 * @param A уменьшаемое
 * @param B вычитаемое
 * @param result матрица разности
 * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления
 */

 int s21_sub_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

 /**
 * @brief Умножение двух матриц
 * @param A первый множитель
 * @param B второй множитель
 * @param result матрица произведения
 * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления
 */

 int s21_mult_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

 /**
 * @brief Умножение матрицы на число
 * @param A исходная матрица
 * @param number множитель
 * @param result матрица произведения
 * @return 0 - OK, 1 - ошибка
 */

 int s21_mult_number(const matrix_t *A, double number, matrix_t *result);

 /**
 * @brief Транспонирование матрицы
 * @param A исходная матрица
 * @param result транспонированная матрица
 * @return 0 - OK, 1 - ошибка
 */

 int s21_transpose(const matrix_t *A, matrix_t *result);

/**
 * @brief Вычисление определителя матрицы
 * @param A исходная квадратная матрица
 * @param result указатель на определитель
 * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления
 */

 int s21_determinant(const matrix_t *A, double *result);

 /**
 * @brief Вычисление матрицы алгебраических дополнений
 * @param A исходная квадратная матрица
 * @param result матрица алгебраических дополнений
 * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления
 */

 int s21_calc_complements(const matrix_t *A, matrix_t *result);

 /**
 * @brief Вычисление обратной матрицы
 * @param A исходная квадратная матрица
 * @param result обратная матрица
 * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления (det = 0)
 */

 int s21_inverse_matrix(const matrix_t *A, matrix_t *result);

#endif //S21_MATRIX_H