#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int return_code = (dst) ? 0 : 1;
  if (!return_code) {
    s21_decimal temp;
    set_null_decimal(&temp);
    s21_truncate(src, &temp);
    uint32_t first_bit = MAXFORBIT & temp.bits[0];
    return_code =
        (temp.bits[2] || temp.bits[1] || first_bit > 0x7fffffff) ? 1 : 0;
    if (!return_code) *dst = (get_sign(temp)) ? -temp.bits[0] : temp.bits[0];
  }
  return return_code;
}