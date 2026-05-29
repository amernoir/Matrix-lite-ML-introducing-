#include <stdio.h>
#include "s21_matrix.h"

int main() {
    matrix_t A = {0};
    matrix_t B = {0};
    matrix_t result = {0};
    
    printf("1. Создаём матрицу A (2x3)...\n");
    int err1 = s21_create_matrix(2, 3, &A);
    printf("   Результат: %d\n", err1);
    
    printf("2. Создаём матрицу B (3x2)...\n");
    int err2 = s21_create_matrix(3, 2, &B);
    printf("   Результат: %d\n", err2);
    
    printf("3. Заполняем матрицу A...\n");
    double a_data[] = {2, 3, 4, 1, 4, 5};
    for (int i = 0; i < 6; ++i) {
        A.data[i] = a_data[i];
    }
    printf("   Готово\n");
    
    printf("4. Заполняем матрицу B...\n");
    double b_data[] = {3, 4, 2, 3, 4, 5};
    for (int i = 0; i < 6; ++i) {
        B.data[i] = b_data[i];
    }
    printf("   Готово\n");
    
    printf("5. Выводим матрицу A:\n");
    for (int i = 0; i < A.rows; ++i) {
        for (int j = 0; j < A.columns; ++j) {
            printf("%.0f ", A.data[i * A.columns + j]);
        }
        printf("\n");
    }
    
    printf("6. Выводим матрицу B:\n");
    for (int i = 0; i < B.rows; ++i) {
        for (int j = 0; j < B.columns; ++j) {
            printf("%.0f ", B.data[i * B.columns + j]);
        }
        printf("\n");
    }
    
    printf("7. Умножаем матрицы...\n");
    int error = s21_mult_matrix_basic(&A, &B, &result);
    printf("   Код ошибки: %d\n", error);
    
    if (error == S21_OK) {
        printf("8. Результат умножения:\n");
        for (int i = 0; i < result.rows; ++i) {
            for (int j = 0; j < result.columns; ++j) {
                printf("%.0f ", result.data[i * result.columns + j]);
            }
            printf("\n");
        }
    } else {
        printf("Ошибка умножения!\n");
    }
    
    printf("9. Очищаем память...\n");
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    printf("10. Готово!\n");
    


    matrix_t C = {0};
    double result1 = 0;

    s21_create_matrix(4,4,&A);
    for (int i = 0; i < 4 * 4; ++i){
        A.data[i] = i + 1;
    }

    s21_determinant(&A, &result1);
    s21_remove_matrix(&A);
    return 0;



    matrix_t mat = {0};
s21_create_matrix(3, 3, &mat);  // OK, mat.data выделен
s21_create_matrix(5, 5, &mat);  // OK, старая память освобождена, новая выделена
s21_remove_matrix(&mat);         // OK
s21_remove_matrix(&mat);         // OK, повторный вызов безопасен
}