#include "../../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = OK;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    code = INCORRECT_MATRIX;
  } else {
    result->columns = columns;
    result->rows = rows;
    /// используем способ для однократного вызова malloc
    result->matrix = (double **)malloc(sizeof(double *) * rows +
                                       sizeof(double) * columns * rows);
    result->matrix[0] = (double *)(result->matrix + rows);
    for (int i = 1; i < rows; ++i) {
      result->matrix[i] = result->matrix[0] + i * columns;
    }
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        result->matrix[i][j] = 0;
      }
    }
  }
  return code;
}