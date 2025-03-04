#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int return_code = (is_correct_decimal(value) && result != NULL) ? 0 : 1;
  if (return_code == 0) {
    if (is_zero(value)) {
      set_null_decimal(result);
    } else {
      s21_extended_decimal ext_value = convert_to_extended(value);
      while (ext_value.scale > 0) {
        remove_digit_from_end(&ext_value);
      }
      *result = convert_to_s21_decimal(ext_value);
    }
  }
  return return_code;
}