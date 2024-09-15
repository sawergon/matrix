#include "../../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = OK;
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B) ||
      result == NULL) {
    code = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    code = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < B->columns; ++j) {
        for (int k = 0; k < B->rows; ++k) {
          result->matrix[i][j] += B->matrix[k][j] * A->matrix[i][k];
        }
      }
    }
  }
  return code;
}