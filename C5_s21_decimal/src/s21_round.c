#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int return_code = (is_correct_decimal(value) && result != NULL) ? 0 : 1;
  if (is_zero(value) && !return_code) {
    set_null_decimal(result);
  } else if (return_code == 0) {
    int remainder = 0;
    s21_extended_decimal ext_value = convert_to_extended(value);
    int counter = 0;
    while (ext_value.scale > 0) {
      remainder = remove_digit_from_end(&ext_value);
      if (remainder != 0) counter++;
    }
    if (bank_rounding(ext_value, remainder, counter)) add_num(&ext_value, 1);
    *result = convert_to_s21_decimal(ext_value);
  }
  return return_code;
}