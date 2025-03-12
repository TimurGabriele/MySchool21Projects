#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (!A || !B || !result) {
    flag = INCORRECT_MATRIX;
  } else if (!is_eq_mat_size(A, B)) {
    flag = CALCULATION_ERROR;
  } else {
    int rows = A->rows;
    int columns = A->columns;

    if (s21_create_matrix(rows, columns, result)) flag = INCORRECT_MATRIX;

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < columns; j++) {
        double sum = A->matrix[i][j] - B->matrix[i][j];
        if (isinf(fabs(sum)) || isnan(fabs(sum))) flag = 2;
        if (!flag) result->matrix[i][j] = sum;
      }
  }
  return flag;
}