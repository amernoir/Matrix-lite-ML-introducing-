    /**
    * @file s21_matrix_func_declare.h
    * @brief ВНУТРЕННИЕ функции библиотеки, не для пользования пользователем 
    * @details header file для вспомогательных функций, предназначенных 
    * для реализации матричных операций
    * @author fairyjac   
    */

    #ifndef S21_MATRIX_PRIVATE_H
    #define S21_MATRIX_PRIVATE_H

    #include "s21_matrix_types.h"

    /**
    * @brief создание матрицы
    * @param rows строки
    * @param columns колонки 
    * @param result указатель на ячейку памяти размерностью rows * columns
    * @return - 0 - OK
    * @return - 1 - error
    */

    int matrix_allocate(int rows, int columns, matrix_t *result);

    /**
        * @brief free resource 
        * @param A pointer to current matrix 
    */

    void matrix_free(matrix_t *A);

    /**
    * @brief проверка на корректность матрицы
    * @param A pointer to current matrix
    * @return 1 - correct, 0 - uncorrect 
    */

    int matrix_is_valid(const matrix_t *A);

/**
 * @brief Заполнение буфера данными подматрицы (удаление строки и столбца)
 * @param A исходная матрица
 * @param n размер исходной подматрицы
 * @param row удаляемая строка (относительно текущего смещения)
 * @param col удаляемый столбец
 * @param buf целевой буфер (row-major)
 * @param buf_offset смещение в буфере
 */
void matrix_fill_minor_buffer(const matrix_t *A, int n, int row, int col,
                              double *buf, int buf_offset);

    /**
    * @brief копирование матриц
    * @param src исходная матрица
    * @param dst целевая матрица
    * @return 0 - ok, 1 - error 
    */

    int matrix_copy_data(const matrix_t *src, matrix_t *dst);

    /**
    * @brief Рекурсивное вычисление определителя
    * @param A исходная матрица
    * @param result указатель на результат
    * @param n размер подматрицы
    * @param row смещение по строкам
    * @param col смещение по столбцам
    * @param buf буфер для подматриц
    * @param buf_offset смещение в буфере
    * @return 0 - OK, 1 - ошибка, 2 - ошибка вычисления
    */
    int determinant_recursive(const matrix_t *A, double *result, int n,
                            int row, int col, double *buf, int buf_offset);

    /**
    * @brief Применение бинарной операции к элементам двух матриц. применение паттерна стратегия 
    */

    int matrix_apply_binary(const matrix_t *A, const matrix_t *B, matrix_t *result,
                            double (*op)(double, double, double), double param);

    /**
    * @brief Применение унарной операции к элементам матрицы
    */

    int matrix_apply_unary(const matrix_t *A, matrix_t *result,
                        double (*op)(double, double), double param);

    #endif