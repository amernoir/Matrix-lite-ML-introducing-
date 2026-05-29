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