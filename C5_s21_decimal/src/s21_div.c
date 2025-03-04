#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code =
      (result && is_correct_decimal(value_1) && is_correct_decimal(value_2))
          ? 0
          : 4;
  if (!return_code) {
    set_null_decimal(result);
    if (is_zero(value_2)) {
      return_code = 3;
    } else if (is_zero(value_1)) {
      return_code = 0;
    } else {
      s21_extended_decimal ext_val_1 = convert_to_extended(value_1);
      s21_extended_decimal ext_val_2 = convert_to_extended(value_2);
      s21_extended_decimal ext_res;
      set_null_extended_decimal(&ext_res);
      ext_res.sign = ext_val_1.sign ^ ext_val_2.sign;
      if (ext_val_1.scale < ext_val_2.scale) {
        for (int i = 0; i < ext_val_2.scale - ext_val_1.scale; ++i)
          mult_ten(&ext_val_1);
      } else {
        for (int i = 0; i < ext_val_1.scale - ext_val_2.scale; ++i)
          mult_ten(&ext_val_2);
      }
      if (compare(ext_val_1, shift_left(ext_val_2, 96)) < 0) {
        ext_val_1 = whole_division(ext_val_1, ext_val_2, &ext_res);
        if (!is_ext_zero(ext_val_1))
          fractional_division(ext_val_1, ext_val_2, &ext_res);
      } else
        return_code = (ext_res.sign) ? 2 : 1;
      if (return_code == 0) {
        return_code = normalize(&ext_res);
        *result = convert_to_s21_decimal(ext_res);
      }
    }
  }
  return return_code;
}