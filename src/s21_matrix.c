#include "s21_matrix.h"

int s21_sum_matrix(const matrix_t* A, const matrix_t* B, matrix_t* result) {
  return matrix_apply_binary(A, B, result, add_op, 0.0);
}
