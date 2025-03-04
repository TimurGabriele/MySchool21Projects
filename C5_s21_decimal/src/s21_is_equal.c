#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 0;
  if (is_zero(value_1)) {
    if (is_zero(value_2)) return_code = 1;
  } else if (get_sign(value_1) == get_sign(value_2)) {
    s21_extended_decimal ext_1 = convert_to_extended(value_1);
    s21_extended_decimal ext_2 = convert_to_extended(value_2);
    scale_equalization(&ext_1, &ext_2);
    if (compare(ext_1, ext_2) == 0) return_code = 1;
  }
  return return_code;
}