#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;

  if (!A || !B) {
    flag = FAILURE;
  } else if (!is_eq_mat_size(A, B)) {
    flag = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1E-7) {
          flag = FAILURE;
          break;
        }
      }
  }
  return flag;
}