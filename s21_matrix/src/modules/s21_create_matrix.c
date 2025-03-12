#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;

  if (!result) {
    flag = INCORRECT_MATRIX;
  } else if (rows < 1 || columns < 1) {
    flag = INCORRECT_MATRIX;
    result->matrix = NULL;
  } else {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      flag = INCORRECT_MATRIX;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
      }
      result->rows = rows;
      result->columns = columns;
    }
  }

  return flag;
}