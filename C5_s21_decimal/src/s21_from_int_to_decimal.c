#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int return_code = (dst) ? 0 : 1;
  if (return_code == 0) {
    dst->bits[0] = src > 0 ? src : -src;
    set_scale(dst, 0);
    set_sign(dst, src < 0);
  }
  return return_code;
}