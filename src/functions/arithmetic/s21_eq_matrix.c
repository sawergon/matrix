#include "../../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = SUCCESS;
  if (!s21_is_correct_matrix(A) || !s21_is_correct_matrix(B) ||
      A->rows != B->rows || A->columns != B->columns) {
    code = FAILURE;
  } else {
    for (int i = 0; i < A->rows && code; ++i) {
      for (int j = 0; j < A->columns && code; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          code = FAILURE;
        }
      }
    }
  }
  return code;
}