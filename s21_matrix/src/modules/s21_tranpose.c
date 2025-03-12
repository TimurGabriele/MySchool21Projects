#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if ((!A || !result || !A->matrix) && (A->rows < 1 || A->columns < 1)) {
    flag = INCORRECT_MATRIX;
  } else {
    if (s21_create_matrix(A->columns, A->rows, result))
      flag = INCORRECT_MATRIX;
    else {
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
    }
  }
  return flag;
}