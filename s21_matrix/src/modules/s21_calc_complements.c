#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    flag = INCORRECT_MATRIX;
  } else if (A->rows == 1 || A->columns == 1) {
    flag = CALCULATION_ERROR;
  } else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (!flag) {
      for (int i = 0; i < A->rows && flag == OK; i++) {
        int sign = i % 2 == 0 ? 1 : -1;
        for (int j = 0; j < A->columns && flag == OK; j++) {
          matrix_t *minor = s21_create_minor(i, j, A);
          if (minor == NULL) {
            flag = INCORRECT_MATRIX;
          } else {
            double det = 0;
            flag = s21_determinant(minor, &det);
            if (!isfinite(det)) {
              flag = CALCULATION_ERROR;
            }
            if (!flag) {
              result->matrix[i][j] = sign * det;
              sign = -sign;
            }
            s21_remove_matrix(minor);
            free(minor);
            minor = NULL;
          }
        }
      }
    }
  }
  return flag;
}