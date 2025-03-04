#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int return_code = 0;
  if (is_correct_decimal(value) && result != NULL) {
    *result = value;
    set_sign(result, !get_sign(value));
  } else {
    return_code = 1;
  }
  return return_code;
}