#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;
  if (!A || !B || !result) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows != B->columns)
    flag = CALCULATION_ERROR;
  else {
    int k_max = A->columns;
    if (s21_create_matrix(A->rows, B->columns, result))
      flag = INCORRECT_MATRIX;
    else {
      for (int i = 0; i < result->rows && !flag; i++)
        for (int j = 0; j < result->columns && !flag; j++) {
          double value = 0;
          for (int k = 0; k < k_max; k++)
            value += A->matrix[i][k] * B->matrix[k][j];
          if (isinf(fabs(value)) || isnan(fabs(value)))
            flag = CALCULATION_ERROR;
          if (!flag) result->matrix[i][j] = value;
        }
    }
  }
  return flag;
}