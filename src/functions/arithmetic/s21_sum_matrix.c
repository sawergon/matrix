#include "../../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B) ||
      result == NULL) {
    code = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    code = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return code;
}