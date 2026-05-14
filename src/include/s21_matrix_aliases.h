/**
* @file s21_matrix_aliases.h
* @brief header file with the main aliases which necessary 
* for s21_matrix library 
* @author fairyjac 
*/

#ifndef S21_MATRIX_ALIASES_H
#define S21_MATRIX_ALIASES_H

#define S21_OK          0  //  успешное выполнение
#define S21_ERROR       1  //  общая ошибка (некорректная матрица и т.д.)
#define S21_CALC_ERROR  2  //  ошибка вычисления (вырожденная матрица)

#define S21_INCORRECT_MATRIX  S21_ERROR

#define SUCCESS 1 
#define FAILURE 0
#define S21_TRUE        1
#define S21_FALSE       0
#define S21_FAILURE         S21_FALSE

#define S21_EPS_ABS     1e-6   //  абсолютный допуск, если числа отличаются меньше чем на 1*10^-6, то они равны 
#define S21_EPS_REL     1e-6   //  relative-относительный допуск, считает разницу в 0.0001% от числа

#define S21_MAX_STACK   6      //  если размерность меньше 6x6 включительно используем VLA, т е проводим вычисления на стеке 
#define S21_MAX_RECURS  15     //  макс. размер для рекурсивного метода

#endif // S21_MATRIX_ALIASES_H