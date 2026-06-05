#include <check.h>
#include <stdlib.h>
#include <math.h>
#include "../s21_matrix.h"
#include "../include/s21_matrix_aliases.h"

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================

void fill_matrix(matrix_t *A, double value) {
    int size = A->rows * A->columns;
    for (int i = 0; i < size; i++) {
        A->data[i] = value;
    }
}

void fill_matrix_sequential(matrix_t *A) {
    int size = A->rows * A->columns;
    for (int i = 0; i < size; i++) {
        A->data[i] = (double)(i + 1);
    }
}

int is_matrix_equal(matrix_t *A, matrix_t *B) {
    if (A->rows != B->rows || A->columns != B->columns) {
        return 0;
    }
    int size = A->rows * A->columns;
    for (int i = 0; i < size; i++) {
        if (fabs(A->data[i] - B->data[i]) > S21_EPS) {
            return 0;
        }
    }
    return 1;
}

// ==================== ТЕСТЫ ДЛЯ s21_create_matrix ====================

START_TEST(test_create_matrix_ok) {
    matrix_t A = {0};
    int result = s21_create_matrix(3, 4, &A);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_int_eq(A.rows, 3);
    ck_assert_int_eq(A.columns, 4);
    ck_assert_ptr_nonnull(A.data);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_invalid_rows) {
    matrix_t A = {0};
    int result = s21_create_matrix(0, 4, &A);
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_invalid_columns) {
    matrix_t A = {0};
    int result = s21_create_matrix(3, -1, &A);
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
    int result = s21_create_matrix(3, 4, NULL);
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_create_matrix_reuse) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    fill_matrix_sequential(&A);
    
    // Повторное создание поверх существующей матрицы
    int result = s21_create_matrix(3, 3, &A);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_int_eq(A.rows, 3);
    ck_assert_int_eq(A.columns, 3);
    
    s21_remove_matrix(&A);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_remove_matrix ====================

START_TEST(test_remove_matrix_ok) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    
    s21_remove_matrix(&A);
    
    ck_assert_ptr_null(A.data);
    ck_assert_int_eq(A.rows, 0);
    ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null) {
    // Просто не должно упасть
    s21_remove_matrix(NULL);
}
END_TEST

START_TEST(test_remove_matrix_already_empty) {
    matrix_t A = {0};
    // Двойной вызов remove_matrix
    s21_remove_matrix(&A);
    s21_remove_matrix(&A);
    // Не должно упасть
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_eq_matrix ====================

START_TEST(test_eq_matrix_equal) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    fill_matrix_sequential(&A);
    fill_matrix_sequential(&B);
    
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal_value) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    fill_matrix_sequential(&A);
    fill_matrix(&B, 10.0);
    
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, FAILURE);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_rows) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 2, &B);
    
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, FAILURE);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_columns) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 3, &B);
    
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, FAILURE);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_invalid_matrix) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(2, 2, &A);
    
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, FAILURE);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_with_eps_precision) {
    matrix_t A = {0}, B = {0};
    s21_create_matrix(1, 1, &A);
    s21_create_matrix(1, 1, &B);
    
    A.data[0] = 1.0000001;
    B.data[0] = 1.0;
    
    // Разница 1e-7, что меньше S21_EPS (1e-6)
    int result = s21_eq_matrix(&A, &B);
    
    ck_assert_int_eq(result, SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_determinant ====================

START_TEST(test_determinant_1x1) {
    matrix_t A = {0};
    s21_create_matrix(1, 1, &A);
    A.data[0] = 5.0;
    
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_double_eq_tol(det, 5.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    // |1 2|
    // |3 4| = 1*4 - 2*3 = 4 - 6 = -2
    A.data[0] = 1.0; A.data[1] = 2.0;
    A.data[2] = 3.0; A.data[3] = 4.0;
    
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_double_eq_tol(det, -2.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    // |1 2 3|
    // |4 5 6| = 0
    // |7 8 9|
    A.data[0] = 1.0; A.data[1] = 2.0; A.data[2] = 3.0;
    A.data[3] = 4.0; A.data[4] = 5.0; A.data[5] = 6.0;
    A.data[6] = 7.0; A.data[7] = 8.0; A.data[8] = 9.0;
    
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_double_eq_tol(det, 0.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3_nonzero) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    // |2 5 7|
    // |6 3 4| = -1
    // |5 -2 -3|
    A.data[0] = 2.0; A.data[1] = 5.0; A.data[2] = 7.0;
    A.data[3] = 6.0; A.data[4] = 3.0; A.data[5] = 4.0;
    A.data[6] = 5.0; A.data[7] = -2.0; A.data[8] = -3.0;
    
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_double_eq_tol(det, -1.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_not_square) {
    matrix_t A = {0};
    s21_create_matrix(2, 3, &A);
    
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_CALC_ERROR);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_invalid_matrix) {
    matrix_t A = {0};
    double det = 0;
    int result = s21_determinant(&A, &det);
    
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_determinant_null_result) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    
    int result = s21_determinant(&A, NULL);
    
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
    
    s21_remove_matrix(&A);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ КОПИРОВАНИЯ ====================

START_TEST(test_copy_matrix_ok) {
    matrix_t src = {0}, dst = {0};
    s21_create_matrix(2, 3, &src);
    s21_create_matrix(2, 3, &dst);
    
    fill_matrix_sequential(&src);
    
    int result = s21_copy_matrix(&src, &dst);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_int_eq(is_matrix_equal(&src, &dst), 1);
    
    s21_remove_matrix(&src);
    s21_remove_matrix(&dst);
}
END_TEST

START_TEST(test_copy_matrix_different_size) {
    matrix_t src = {0}, dst = {0};
    s21_create_matrix(2, 3, &src);
    s21_create_matrix(3, 2, &dst);
    
    int result = s21_copy_matrix(&src, &dst);
    
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
    
    s21_remove_matrix(&src);
    s21_remove_matrix(&dst);
}
END_TEST

START_TEST(test_copy_matrix_invalid_src) {
    matrix_t src = {0}, dst = {0};
    s21_create_matrix(2, 2, &dst);
    
    int result = s21_copy_matrix(&src, &dst);
    
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
    
    s21_remove_matrix(&dst);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ ЗАПОЛНЕНИЯ ====================

START_TEST(test_fill_matrix) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    
    s21_fill_matrix(&A, 5.0);
    
    for (int i = 0; i < 4; i++) {
        ck_assert_double_eq_tol(A.data[i], 5.0, S21_EPS);
    }
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_zero_matrix) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    fill_matrix_sequential(&A);
    
    s21_zero_matrix(&A);
    
    for (int i = 0; i < 4; i++) {
        ck_assert_double_eq_tol(A.data[i], 0.0, S21_EPS);
    }
    
    s21_remove_matrix(&A);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ two_matrix_create ====================

START_TEST(test_two_matrix_create_ok) {
    matrix_t A = {0}, B = {0};
    
    int result = two_matrix_create(2, 2, &A, 3, 3, &B);
    
    ck_assert_int_eq(result, S21_OK);
    ck_assert_int_eq(A.rows, 2);
    ck_assert_int_eq(A.columns, 2);
    ck_assert_int_eq(B.rows, 3);
    ck_assert_int_eq(B.columns, 3);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_two_matrix_create_second_fails) {
    matrix_t A = {0}, B = {0};
    
    // Создаём вторую с неверными размерами
    int result = two_matrix_create(2, 2, &A, 0, 3, &B);
    
    // Первая должна быть удалена, вторая не создана
    ck_assert_int_eq(result, S21_INCORRECT_MATRIX);
    ck_assert_ptr_null(A.data);
    ck_assert_int_eq(A.rows, 0);
    ck_assert_int_eq(A.columns, 0);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_mult_matrix ====================

START_TEST(test_mult_matrix_2x2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    
    // A = |1 2|
    //     |3 4|
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    
    // B = |5 6|
    //     |7 8|
    B.data[0] = 5; B.data[1] = 6;
    B.data[2] = 7; B.data[3] = 8;
    
    // Ожидаемый результат:
    // |1*5+2*7 = 19   1*6+2*8 = 22|
    // |3*5+4*7 = 43   3*6+4*8 = 50|
    
    int result_code = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(result_code, S21_OK);
    ck_assert_double_eq_tol(result.data[0], 19.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[1], 22.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[2], 43.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[3], 50.0, S21_EPS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_2x3_3x2) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &B);
    
    // A = |1 2 3|
    //     |4 5 6|
    for (int i = 0; i < 6; i++) A.data[i] = i + 1;
    
    // B = |7  8 |
    //     |9 10 |
    //     |11 12|
    for (int i = 0; i < 6; i++) B.data[i] = i + 7;
    
    // Результат: 2x2
    // C[0,0] = 1*7 + 2*9 + 3*11 = 7 + 18 + 33 = 58
    // C[0,1] = 1*8 + 2*10 + 3*12 = 8 + 20 + 36 = 64
    // C[1,0] = 4*7 + 5*9 + 6*11 = 28 + 45 + 66 = 139
    // C[1,1] = 4*8 + 5*10 + 6*12 = 32 + 50 + 72 = 154
    
    int result_code = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(result_code, S21_OK);
    ck_assert_int_eq(result.rows, 2);
    ck_assert_int_eq(result.columns, 2);
    ck_assert_double_eq_tol(result.data[0], 58.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[1], 64.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[2], 139.0, S21_EPS);
    ck_assert_double_eq_tol(result.data[3], 154.0, S21_EPS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_incompatible) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(2, 2, &B);
    
    int result_code = s21_mult_matrix(&A, &B, &result);
    
    ck_assert_int_eq(result_code, S21_CALC_ERROR);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_sum_matrix ====================

START_TEST(test_sum_matrix_ok) {
    matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &expected);
    
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    B.data[0] = 5; B.data[1] = 6;
    B.data[2] = 7; B.data[3] = 8;
    expected.data[0] = 6; expected.data[1] = 8;
    expected.data[2] = 10; expected.data[3] = 12;
    
    int status = s21_sum_matrix(&A, &B, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_matrix_diff_size) {
    matrix_t A = {0}, B = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(3, 2, &B);
    
    int status = s21_sum_matrix(&A, &B, &result);
    
    ck_assert_int_eq(status, S21_CALC_ERROR);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_invalid) {
    matrix_t A = {0}, B = {0}, result = {0};
    
    int status = s21_sum_matrix(&A, &B, &result);
    
    ck_assert_int_eq(status, S21_INCORRECT_MATRIX);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_sub_matrix ====================

START_TEST(test_sub_matrix_ok) {
    matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &B);
    s21_create_matrix(2, 2, &expected);
    
    A.data[0] = 5; A.data[1] = 6;
    A.data[2] = 7; A.data[3] = 8;
    B.data[0] = 1; B.data[1] = 2;
    B.data[2] = 3; B.data[3] = 4;
    expected.data[0] = 4; expected.data[1] = 4;
    expected.data[2] = 4; expected.data[3] = 4;
    
    int status = s21_sub_matrix(&A, &B, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_mult_number ====================

START_TEST(test_mult_number_ok) {
    matrix_t A = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &expected);
    
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    expected.data[0] = 2; expected.data[1] = 4;
    expected.data[2] = 6; expected.data[3] = 8;
    
    int status = s21_mult_number(&A, 2.0, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_transpose ====================

START_TEST(test_transpose_2x3) {
    matrix_t A = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 3, &A);
    s21_create_matrix(3, 2, &expected);
    
    A.data[0] = 1; A.data[1] = 2; A.data[2] = 3;
    A.data[3] = 4; A.data[4] = 5; A.data[5] = 6;
    expected.data[0] = 1; expected.data[1] = 4;
    expected.data[2] = 2; expected.data[3] = 5;
    expected.data[4] = 3; expected.data[5] = 6;
    
    int status = s21_transpose(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

// ==================== ТЕСТЫ ДЛЯ s21_inverse_matrix ====================

START_TEST(test_inverse_2x2) {
    matrix_t A = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &expected);
    
    A.data[0] = 4; A.data[1] = 7;
    A.data[2] = 2; A.data[3] = 6;
    expected.data[0] = 0.6; expected.data[1] = -0.7;
    expected.data[2] = -0.2; expected.data[3] = 0.4;
    
    int status = s21_inverse_matrix(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_3x3) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(3, 3, &A);
    
    A.data[0] = 2; A.data[1] = 5; A.data[2] = 7;
    A.data[3] = 6; A.data[4] = 3; A.data[5] = 4;
    A.data[6] = 5; A.data[7] = -2; A.data[8] = -3;
    
    int status = s21_inverse_matrix(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    
    // Проверка: A * A^(-1) = I
    matrix_t check = {0};
    s21_mult_matrix(&A, &result, &check);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            double expected = (i == j) ? 1.0 : 0.0;
            ck_assert_double_eq_tol(check.data[i * 3 + j], expected, S21_EPS);
        }
    }
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&check);
}
END_TEST

START_TEST(test_inverse_singular) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(2, 2, &A);
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 2; A.data[3] = 4;
    
    int status = s21_inverse_matrix(&A, &result);
    
    ck_assert_int_eq(status, S21_CALC_ERROR);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
    matrix_t A = {0}, result = {0}, expected = {0};
    s21_create_matrix(2, 2, &A);
    s21_create_matrix(2, 2, &expected);
    
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    expected.data[0] = 4; expected.data[1] = -3;
    expected.data[2] = -2; expected.data[3] = 1;
    
    int status = s21_calc_complements(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST


// ===================================


// ==================== ТЕСТЫ ДЛЯ БОЛЬШИХ МАТРИЦ (LU-разложение) ====================
// ==================== ТЕСТЫ ДЛЯ БОЛЬШИХ МАТРИЦ (LU РАЗЛОЖЕНИЕ) ====================

START_TEST(test_determinant_7x7_diagonal) {
    matrix_t A = {0};
    s21_create_matrix(7, 7, &A);
    
    // Диагональная матрица: определитель = 1*2*3*4*5*6*7 = 5040
    for (int i = 0; i < 7; i++) {
        A.data[i * 7 + i] = (double)(i + 1);
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 5040.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_8x8_diagonal) {
    matrix_t A = {0};
    s21_create_matrix(8, 8, &A);
    
    // Диагональная матрица: определитель = 1*2*3*4*5*6*7*8 = 40320
    for (int i = 0; i < 8; i++) {
        A.data[i * 8 + i] = (double)(i + 1);
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 40320.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_9x9_identity) {
    matrix_t A = {0};
    s21_create_matrix(9, 9, &A);
    
    // Единичная матрица: определитель = 1
    for (int i = 0; i < 9; i++) {
        A.data[i * 9 + i] = 1.0;
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 1.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_10x10) {
    matrix_t A = {0};
    s21_create_matrix(10, 10, &A);
    
    // Верхнетреугольная матрица с диагональю 1: определитель = 1
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            A.data[i * 10 + j] = (double)(j - i + 1);
        }
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 1.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5x5_random) {
    matrix_t A = {0};
    s21_create_matrix(5, 5, &A);
    
    // Матрица с известным определителем (вычислен заранее = 10)
    A.data[0] = 1; A.data[1] = 0; A.data[2] = 0; A.data[3] = 0; A.data[4] = 0;
    A.data[5] = 0; A.data[6] = 2; A.data[7] = 0; A.data[8] = 0; A.data[9] = 0;
    A.data[10] = 0; A.data[11] = 0; A.data[12] = 3; A.data[13] = 0; A.data[14] = 0;
    A.data[15] = 0; A.data[16] = 0; A.data[17] = 0; A.data[18] = 4; A.data[19] = 0;
    A.data[20] = 0; A.data[21] = 0; A.data[22] = 0; A.data[23] = 0; A.data[24] = 5;
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 120.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4x4_diagonal) {
    matrix_t A = {0};
    s21_create_matrix(4, 4, &A);
    
    // Диагональная матрица: определитель = 2*3*4*5 = 120
    for (int i = 0; i < 4; i++) {
        A.data[i * 4 + i] = (double)(i + 2);
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 120.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_4x4_upper_triangular) {
    matrix_t A = {0};
    s21_create_matrix(4, 4, &A);
    
    // Верхнетреугольная матрица: определитель = произведение диагонали = 1*2*3*4 = 24
    A.data[0] = 1; A.data[1] = 2; A.data[2] = 3; A.data[3] = 4;
    A.data[4] = 0; A.data[5] = 2; A.data[6] = 3; A.data[7] = 4;
    A.data[8] = 0; A.data[9] = 0; A.data[10] = 3; A.data[11] = 4;
    A.data[12] = 0; A.data[13] = 0; A.data[14] = 0; A.data[15] = 4;
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 24.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_5x5_identity) {
    matrix_t A = {0};
    s21_create_matrix(5, 5, &A);
    
    // Единичная матрица: определитель = 1
    for (int i = 0; i < 5; i++) {
        A.data[i * 5 + i] = 1.0;
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 1.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_6x6) {
    matrix_t A = {0};
    s21_create_matrix(6, 6, &A);
    
    // Диагональная матрица: определитель = 1*2*3*4*5*6 = 720
    for (int i = 0; i < 6; i++) {
        A.data[i * 6 + i] = (double)(i + 1);
    }
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 720.0, S21_EPS);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_1x1) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(1, 1, &A);
    A.data[0] = 5.0;
    
    int status = s21_inverse_matrix(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(result.data[0], 0.2, S21_EPS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST
START_TEST(test_determinant_3x3_lu) {
    matrix_t A = {0};
    s21_create_matrix(3, 3, &A);
    
    A.data[0] = 1; A.data[1] = 2; A.data[2] = 3;
    A.data[3] = 0; A.data[4] = 1; A.data[5] = 4;
    A.data[6] = 5; A.data[7] = 6; A.data[8] = 0;
    
    double det = 0;
    int status = s21_determinant(&A, &det);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(det, 1.0, S21_EPS);  // ← исправлено с 10 на 1
    
    s21_remove_matrix(&A);
}
END_TEST
START_TEST(test_inverse_null_result) {
    matrix_t A = {0};
    s21_create_matrix(2, 2, &A);
    A.data[0] = 1; A.data[1] = 2;
    A.data[2] = 3; A.data[3] = 4;
    
    int status = s21_inverse_matrix(&A, NULL);
    
    ck_assert_int_eq(status, S21_INCORRECT_MATRIX);
    
    s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_invalid_matrix) {
    matrix_t A = {0}, result = {0};
    
    int status = s21_inverse_matrix(&A, &result);
    
    ck_assert_int_eq(status, S21_INCORRECT_MATRIX);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(1, 1, &A);
    A.data[0] = 10.0;
    
    int status = s21_calc_complements(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_double_eq_tol(result.data[0], 1.0, S21_EPS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
    matrix_t A = {0}, result = {0}, expected = {0};
    s21_create_matrix(3, 3, &A);
    s21_create_matrix(3, 3, &expected);
    
    A.data[0] = 1; A.data[1] = 2; A.data[2] = 3;
    A.data[3] = 0; A.data[4] = 4; A.data[5] = 5;
    A.data[6] = 1; A.data[7] = 0; A.data[8] = 6;
    
    // Ожидаемая матрица алгебраических дополнений
    expected.data[0] = 24;  // 4*6 - 5*0 = 24
    expected.data[1] = 5;   // -(0*6 - 5*1) = 5
    expected.data[2] = -4;  // 0*0 - 4*1 = -4
    expected.data[3] = -12; // -(2*6 - 3*0) = -12
    expected.data[4] = 3;   // 1*6 - 3*1 = 3
    expected.data[5] = 2;   // -(1*0 - 2*1) = 2
    expected.data[6] = -2;  // 2*5 - 3*4 = -2
    expected.data[7] = -5;  // -(1*5 - 3*0) = -5
    expected.data[8] = 4;   // 1*4 - 2*0 = 4
    
    int status = s21_calc_complements(&A, &result);
    
    ck_assert_int_eq(status, S21_OK);
    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    
    s21_remove_matrix(&A);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
    matrix_t A = {0}, result = {0};
    s21_create_matrix(2, 3, &A);
    
    int status = s21_calc_complements(&A, &result);
    
    ck_assert_int_eq(status, S21_CALC_ERROR);
    
    s21_remove_matrix(&A);
}
END_TEST

// ==================== MAIN ====================

Suite *s21_matrix_suite(void) {
    Suite *s = suite_create("s21_matrix");
    
    // Core functions
    TCase *tc_create = tcase_create("create");
    tcase_add_test(tc_create, test_create_matrix_ok);
    tcase_add_test(tc_create, test_create_matrix_invalid_rows);
    tcase_add_test(tc_create, test_create_matrix_invalid_columns);
    tcase_add_test(tc_create, test_create_matrix_null_result);
    tcase_add_test(tc_create, test_create_matrix_reuse);
    suite_add_tcase(s, tc_create);
    
    TCase *tc_remove = tcase_create("remove");
    tcase_add_test(tc_remove, test_remove_matrix_ok);
    tcase_add_test(tc_remove, test_remove_matrix_null);
    tcase_add_test(tc_remove, test_remove_matrix_already_empty);
    suite_add_tcase(s, tc_remove);
    
    TCase *tc_eq = tcase_create("eq_matrix");
    tcase_add_test(tc_eq, test_eq_matrix_equal);
    tcase_add_test(tc_eq, test_eq_matrix_not_equal_value);
    tcase_add_test(tc_eq, test_eq_matrix_different_rows);
    tcase_add_test(tc_eq, test_eq_matrix_different_columns);
    tcase_add_test(tc_eq, test_eq_matrix_invalid_matrix);
    tcase_add_test(tc_eq, test_eq_matrix_with_eps_precision);
    suite_add_tcase(s, tc_eq);
    
    TCase *tc_det = tcase_create("determinant");
    tcase_add_test(tc_det, test_determinant_1x1);
    tcase_add_test(tc_det, test_determinant_2x2);
    tcase_add_test(tc_det, test_determinant_3x3);
    tcase_add_test(tc_det, test_determinant_3x3_nonzero);
    tcase_add_test(tc_det, test_determinant_not_square);
    tcase_add_test(tc_det, test_determinant_invalid_matrix);
    tcase_add_test(tc_det, test_determinant_null_result);
    suite_add_tcase(s, tc_det);
    
    TCase *tc_copy = tcase_create("copy");
    tcase_add_test(tc_copy, test_copy_matrix_ok);
    tcase_add_test(tc_copy, test_copy_matrix_different_size);
    tcase_add_test(tc_copy, test_copy_matrix_invalid_src);
    suite_add_tcase(s, tc_copy);
    
    TCase *tc_fill = tcase_create("fill");
    tcase_add_test(tc_fill, test_fill_matrix);
    tcase_add_test(tc_fill, test_zero_matrix);
    suite_add_tcase(s, tc_fill);
    
    TCase *tc_two_create = tcase_create("two_matrix_create");
    tcase_add_test(tc_two_create, test_two_matrix_create_ok);
    tcase_add_test(tc_two_create, test_two_matrix_create_second_fails);
    suite_add_tcase(s, tc_two_create);
    
    TCase *tc_mult = tcase_create("mult_matrix");
    tcase_add_test(tc_mult, test_mult_matrix_2x2);
    tcase_add_test(tc_mult, test_mult_matrix_2x3_3x2);
    tcase_add_test(tc_mult, test_mult_matrix_incompatible);
    suite_add_tcase(s, tc_mult);
    // sum_matrix tests
    TCase *tc_sum = tcase_create("sum_matrix");
    tcase_add_test(tc_sum, test_sum_matrix_ok);
    tcase_add_test(tc_sum, test_sum_matrix_diff_size);
    tcase_add_test(tc_sum, test_sum_matrix_invalid);
    suite_add_tcase(s, tc_sum);
    
    // sub_matrix tests
    TCase *tc_sub = tcase_create("sub_matrix");
    tcase_add_test(tc_sub, test_sub_matrix_ok);
    suite_add_tcase(s, tc_sub);
    
    // mult_number tests
    TCase *tc_mult_num = tcase_create("mult_number");
    tcase_add_test(tc_mult_num, test_mult_number_ok);
    suite_add_tcase(s, tc_mult_num);
    
    // transpose tests
    TCase *tc_transpose = tcase_create("transpose");
    tcase_add_test(tc_transpose, test_transpose_2x3);
    suite_add_tcase(s, tc_transpose);
    
    // inverse_matrix tests
    TCase *tc_inverse = tcase_create("inverse_matrix");
    tcase_add_test(tc_inverse, test_inverse_2x2);
    tcase_add_test(tc_inverse, test_inverse_3x3);
    tcase_add_test(tc_inverse, test_inverse_singular);
    suite_add_tcase(s, tc_inverse);
    
    // calc_complements tests
    TCase *tc_calc = tcase_create("calc_complements");
    tcase_add_test(tc_calc, test_calc_complements_2x2);
    suite_add_tcase(s, tc_calc);
    
 // ===

 // Большие матрицы для determinant
TCase *tc_det_large = tcase_create("determinant_large");
tcase_add_test(tc_det_large, test_determinant_4x4_diagonal);
tcase_add_test(tc_det_large, test_determinant_4x4_upper_triangular);
tcase_add_test(tc_det_large, test_determinant_5x5_identity);
tcase_add_test(tc_det_large, test_determinant_6x6);
suite_add_tcase(s, tc_det_large);

// Дополнительные тесты inverse_matrix
TCase *tc_inverse_more = tcase_create("inverse_matrix_more");
tcase_add_test(tc_inverse_more, test_inverse_1x1);
tcase_add_test(tc_inverse_more, test_inverse_null_result);
tcase_add_test(tc_inverse_more, test_inverse_invalid_matrix);
suite_add_tcase(s, tc_inverse_more);

// Дополнительные тесты calc_complements
TCase *tc_calc_more = tcase_create("calc_complements_more");
tcase_add_test(tc_calc_more, test_calc_complements_1x1);
tcase_add_test(tc_calc_more, test_calc_complements_3x3);
tcase_add_test(tc_calc_more, test_calc_complements_not_square);
suite_add_tcase(s, tc_calc_more);

// Ещё большие матрицы для LU-разложения
TCase *tc_det_lu = tcase_create("determinant_lu");
tcase_add_test(tc_det_lu, test_determinant_7x7_diagonal);
tcase_add_test(tc_det_lu, test_determinant_8x8_diagonal);
tcase_add_test(tc_det_lu, test_determinant_9x9_identity);
tcase_add_test(tc_det_lu, test_determinant_10x10);
tcase_add_test(tc_det_lu, test_determinant_5x5_random);
tcase_add_test(tc_det_lu, test_determinant_3x3_lu);
suite_add_tcase(s, tc_det_lu);
    return s;
}

int main(void) {
    Suite *s = s21_matrix_suite();
    SRunner *sr = srunner_create(s);
    
    srunner_run_all(sr, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return (number_failed == 0) ? 0 : 1;
}