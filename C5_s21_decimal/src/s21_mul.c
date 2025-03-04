#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_code = result ? 0 : 4;
  set_null_decimal(result);
  if (!return_code) {
    set_null_decimal(result);
    if (!is_zero(value_1) && !is_zero(value_2)) {
      s21_extended_decimal ext_val_1 = convert_to_extended(value_1),
                           ext_val_2 = convert_to_extended(value_2), ext_res;
      set_null_extended_decimal(&ext_res);
      ext_res.scale = ext_val_1.scale + ext_val_2.scale;
      ext_res.sign = ext_val_1.sign ^ ext_val_2.sign;
      sum_ext_bits(&ext_res, 0, ext_val_1.bits[0] * ext_val_2.bits[0], 0, 0);
      sum_ext_bits(&ext_res, 1, ext_val_1.bits[1] * ext_val_2.bits[0],
                   ext_val_1.bits[0] * ext_val_2.bits[1], 0);
      sum_ext_bits(&ext_res, 2, ext_val_1.bits[0] * ext_val_2.bits[2],
                   ext_val_1.bits[1] * ext_val_2.bits[1],
                   ext_val_1.bits[2] * ext_val_2.bits[0]);
      sum_ext_bits(&ext_res, 3, ext_val_1.bits[1] * ext_val_2.bits[2],
                   ext_val_1.bits[2] * ext_val_2.bits[1], 0);
      sum_ext_bits(&ext_res, 4, ext_val_1.bits[2] * ext_val_2.bits[2], 0, 0);
      return_code = normalize(&ext_res);
      if (return_code)
        return_code = (ext_res.sign) ? 2 : 1;
      else
        *result = convert_to_s21_decimal(ext_res);
    }
  }
  return return_code;
}