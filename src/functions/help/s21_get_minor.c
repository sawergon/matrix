#include "../../s21_matrix.h"

void s21_get_minor(matrix_t *matrix, matrix_t *result, int i, int j, int size) {
  int di = 0, dj;
  for (int ki = 0; ki < size - 1; ki++) {
    if (ki == i) di = 1;
    dj = 0;
    for (int kj = 0; kj < size - 1; kj++) {
      if (kj == j) dj = 1;
      result->matrix[ki][kj] = matrix->matrix[ki + di][kj + dj];
    }
  }
}