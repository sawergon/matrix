#include "../../s21_matrix.h"

bool s21_is_correct_matrix(matrix_t *matrix) {
  return matrix != NULL && matrix->matrix != NULL && matrix->rows > 0 &&
         matrix->columns > 0;
}