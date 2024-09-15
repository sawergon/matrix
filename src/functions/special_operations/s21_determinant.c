#include "../../s21_matrix.h"

double determinant(matrix_t *matrix, int size);

int s21_determinant(matrix_t *A, double *result) {
  int code = OK;
  if (!s21_is_correct_matrix(A) || result == NULL) {
    code = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    code = CALC_ERROR;
  } else {
    *result = determinant(A, A->rows);
  }
  return code;
}

double determinant(matrix_t *matrix, int size) {
  int minus_one_degree = 1, n = size - 1;
  double result = 0;
  if (size == 1) {
    result = matrix->matrix[0][0];
  } else if (size == 2) {
    result = matrix->matrix[0][0] * matrix->matrix[1][1] -
             (matrix->matrix[1][0] * matrix->matrix[0][1]);
  } else {
    matrix_t p;
    s21_create_matrix(n, n, &p);
    for (int i = 0; i < size; i++) {
      s21_get_minor(matrix, &p, i, 0, size);
      result =
          result + minus_one_degree * matrix->matrix[i][0] * determinant(&p, n);
      minus_one_degree = -minus_one_degree;
    }
    s21_remove_matrix(&p);
  }
  return result;
}