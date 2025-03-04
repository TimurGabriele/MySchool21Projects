#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_code = (dst) ? 0 : 1;
  if (isnan(src)) return_code = 1;
  if (!return_code) set_null_decimal(dst);
  if (src && !return_code) {
    int sign = (src < 0) ? 1 : 0;
    src = fabs(src);
    if (src < 1e-28 || src > 7.92281625e28)
      return_code = 1;
    else {
      char ch[15];
      sprintf(ch, "%+.6e", src);
      int val = char_to_num(ch[1]);
      for (int i = 3; i < 9; ++i) val = 10 * val + char_to_num(ch[i]);
      int scale = 0;
      sscanf(ch + 10, "%d", &scale);
      scale -= 6;
      s21_extended_decimal ext_val;
      set_null_extended_decimal(&ext_val);
      ext_val.bits[0] = val;
      ext_val.sign = sign;
      if (scale > 0) {
        for (int i = 0; i < scale; ++i) return_code = mult_ten(&ext_val);
      } else {
        ext_val.scale = -scale;
        return_code = normalize(&ext_val);
      }
      *dst = convert_to_s21_decimal(ext_val);
    }
  }
  return return_code;
}