/**
 * @file s21_matrix_types.h 
 * @brief header file for store structures and data type
 * for matrix library 
 * @author fairyjac 
*/

#ifndef S21_MATRIX_TYPES_H
#define S21_MATRIX_TYPES_H

/**
    * @struct matrix_t
    * @brief структура хранящая данные двойной точности 
    * (double precision) с динамическим выделением ресурсов
    * @note реализация матрицы придерживается row-major подхода, при
    * котором аллокация данных состоит в выделении памяти под один непрервный
    * блок RAM, что обеспечивает значительные преимущества в отличие от column-major 
    * порядка  
*/

typedef struct matrix {
    double *data;
    int rows;
    int columns;
} matrix_t;

#endif