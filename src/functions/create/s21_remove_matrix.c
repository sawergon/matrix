#include "../../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    /// поскольку при выделении однократный вызов, то тут тоже
    free(A->matrix);
    A->matrix = NULL;
    /// дополнительно зануляем стобцы и строки
    A->rows = 0;
    A->columns = 0;
  }
}
