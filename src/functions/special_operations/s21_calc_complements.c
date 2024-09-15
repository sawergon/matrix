#include "../../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    code = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    code = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t minor;
    int matrix_size = A->rows, minor_size = matrix_size - 1;
    if (matrix_size == 1) {
      code = CALC_ERROR;
      s21_remove_matrix(result);
    } else {
      int minus_one_degree = 1;
      for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
          minus_one_degree = (((i + j) & 1) == 0) ? 1 : -1;
          s21_create_matrix(minor_size, minor_size, &minor);
          s21_get_minor(A, &minor, i, j, matrix_size);
          double minor_determinant = 0;
          s21_determinant(&minor, &minor_determinant);
          result->matrix[i][j] = minus_one_degree * minor_determinant;
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return code;
}
