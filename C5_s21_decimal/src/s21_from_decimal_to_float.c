#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int return_code = dst ? 0 : 1;
  if (is_zero(src) && return_code == 0)
    *dst = 0;
  else if (!return_code) {
    int sign = (get_sign(src)) ? -1 : 1;
    int exp = (src.bits[3] & 0x7fffffff) >> 16;
    uint32_t value[3];
    for (int i = 0; i < 3; ++i) value[i] = (unsigned int)src.bits[i];
    *dst = (pow(2, 64) * value[2] + pow(2, 32) * value[1] + value[0]) *
           pow(10, -exp) * sign;
  }
  return return_code;
}