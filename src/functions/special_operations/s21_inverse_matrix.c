#include "../../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = OK;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    code = INCORRECT_MATRIX;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (det != 0) {
      matrix_t alg_dop_matrix;
      s21_calc_complements(A, &alg_dop_matrix);
      matrix_t transpose_alg_dop_matrix;
      s21_transpose(&alg_dop_matrix, &transpose_alg_dop_matrix);
      s21_mult_number(&transpose_alg_dop_matrix, 1 / det, result);
      s21_remove_matrix(&alg_dop_matrix);
      s21_remove_matrix(&transpose_alg_dop_matrix);
    } else {
      code = CALC_ERROR;
    }
  }
  return code;
}
