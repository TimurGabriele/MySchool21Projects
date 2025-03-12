#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = OK;
  if (!A || !result) {
    flag = INCORRECT_MATRIX;
  } else {
    int rows = A->rows;
    int columns = A->columns;

    if (s21_create_matrix(rows, columns, result)) {
      flag = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
          double sum = A->matrix[i][j] * number;
          if (isinf(fabs(sum)) || isnan(fabs(sum))) flag = 2;
          if (!flag) result->matrix[i][j] = sum;
        }
    }
  }
  return flag;
}