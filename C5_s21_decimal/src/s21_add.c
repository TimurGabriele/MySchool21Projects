#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code =
      (is_correct_decimal(value_1) && is_correct_decimal(value_2)) ? 0 : 4;
  set_null_decimal(result);
  if ((is_zero(value_1) || is_zero(value_2)) && !return_code) {
    *result = is_zero(value_1) ? decimal_remove_trailing_zeroes(value_1)
                               : decimal_remove_trailing_zeroes(value_2);
  } else if (!return_code) {
    s21_extended_decimal ext_value_1 = convert_to_extended(value_1);
    s21_extended_decimal ext_value_2 = convert_to_extended(value_2);
    s21_extended_decimal ext_res;
    set_null_extended_decimal(&ext_res);
    return_code = scale_equalization(&ext_value_1, &ext_value_2);
    if (ext_value_1.sign == ext_value_2.sign) {
      ext_res = sum_by_bits(ext_value_1, ext_value_2);
    } else {
      int greater_num = compare(ext_value_1, ext_value_2);
      if (greater_num == 1) {
        ext_res = calculate_bits_diff(ext_value_1, ext_value_2);
      } else if (greater_num == -1) {
        ext_value_1.sign = ext_value_2.sign;
        ext_res = calculate_bits_diff(ext_value_2, ext_value_1);
      }
    }
    return_code = normalize(&ext_res);
    if (return_code)
      return_code = (ext_value_1.sign) ? 2 : 1;
    else
      *result = convert_to_s21_decimal(ext_res);
  }
  return return_code;
}