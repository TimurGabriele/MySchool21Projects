#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int return_code = (!is_correct_decimal(value) || !result) ? 1 : 0;
  if (!return_code) {
    set_null_decimal(result);
    if (!is_zero(value)) {
      int flag_notint = 0;
      s21_extended_decimal ext_decimal = convert_to_extended(value);
      while (ext_decimal.scale) {
        int remainder = remove_digit_from_end(&ext_decimal);
        flag_notint = (flag_notint) ? flag_notint : remainder;
      }
      if (flag_notint && ext_decimal.sign) add_num(&ext_decimal, 1);
      *result = convert_to_s21_decimal(ext_decimal);
    }
  }
  return return_code;
}