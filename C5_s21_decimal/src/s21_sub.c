#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal tmp = {0};
  s21_negate(value_2, &tmp);
  return s21_add(value_1, tmp, result);
}