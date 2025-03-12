#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;

  if (A == NULL || A->matrix == NULL || result == NULL)
    flag = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    flag = CALCULATION_ERROR;
  else {
    if (A->rows == 1) *result = A->matrix[0][0];
    if (A->rows == 2)
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    if (A->rows == 3)
      *result = A->matrix[0][0] * A->matrix[1][1] * A->matrix[2][2] +
                A->matrix[2][0] * A->matrix[0][1] * A->matrix[1][2] +
                A->matrix[1][0] * A->matrix[2][1] * A->matrix[0][2] -
                A->matrix[2][0] * A->matrix[1][1] * A->matrix[0][2] -
                A->matrix[0][0] * A->matrix[2][1] * A->matrix[1][2] -
                A->matrix[1][0] * A->matrix[0][1] * A->matrix[2][2];
    if (A->rows > 3) {
      int sign = 1;
      *result = 0;
      for (int i = 0; i < A->columns && flag == OK; i++) {
        matrix_t *minor = s21_create_minor(0, i, A);
        if (minor == NULL) {
          flag = INCORRECT_MATRIX;
        } else {
          double minor_det = 0;
          flag = s21_determinant(minor, &minor_det);
          if (!flag) {
            *result += sign * A->matrix[0][i] * minor_det;
            sign = -sign;
          }
          s21_remove_matrix(minor);
          free(minor);
          minor = NULL;
        }
      }
    }
  }
  return flag;
}