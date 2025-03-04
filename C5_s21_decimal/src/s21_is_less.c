#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int return_code = 0;
  if (is_zero(value_1)) {
    if (!is_zero(value_2)) return_code = (get_sign(value_2)) ? 0 : 1;
  } else if (is_zero(value_2))
    return_code = (get_sign(value_1)) ? 1 : 0;
  else {
    int sign_1 = get_sign(value_1), sign_2 = get_sign(value_2);
    if (sign_1 != sign_2)
      return_code = (sign_1 > sign_2) ? 1 : 0;
    else {
      s21_extended_decimal v_1 = convert_to_extended(value_1),
                           v_2 = convert_to_extended(value_2);
      scale_equalization(&v_1, &v_2);
      int who_grate = compare(v_1, v_2);
      if (who_grate == 1)
        return_code = (sign_1) ? 1 : 0;
      else if (who_grate == -1)
        return_code = (sign_1) ? 0 : 1;
    }
  }
  return return_code;
}