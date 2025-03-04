#include "s21_decimal.h"

int get_bit(unsigned int value, int idx) {
  int mask = 1 << idx;
  return (value & mask) >> idx;
}

void set_bit(unsigned int *num, int idx, int value) {
  unsigned int mask = 1 << idx;
  if (value) {
    *num |= mask;
  } else {
    *num &= ~mask;
  }
};

int get_sign(s21_decimal decimal) { return get_bit(decimal.bits[3], 31); }

void set_sign(s21_decimal *decimal, int sign) {
  set_bit(&decimal->bits[3], 31, sign);
}

int get_scale(s21_decimal decimal) {
  return (decimal.bits[3] & SCALE_MASK) >> SCALE_SHIFT;
}

void set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= ~SCALE_MASK;
  decimal->bits[3] |= scale << SCALE_SHIFT;
}

unsigned int get_overflow(uint64_t value) { return value >> 32; }

int is_zero(s21_decimal decimal) {
  int is_zero = 1;
  for (int i = 0; i < 3; i++) {
    if (decimal.bits[i] != 0) {
      is_zero = 0;
      break;
    }
  }
  return is_zero;
}

int is_correct_decimal(s21_decimal decimal) {
  int is_correct = 1;
  for (int i = 0; i < 16; i++) {
    if (get_bit(decimal.bits[3], i)) {
      is_correct = 0;
      break;
    }
  }
  if (is_correct) {
    for (int i = 24; i < 31; i++) {
      if (get_bit(decimal.bits[3], i)) {
        is_correct = 0;
        break;
      }
    }
  }
  if (is_correct) {
    if (get_scale(decimal) > 28 || get_scale(decimal) < 0) is_correct = 0;
  }
  return is_correct;
}

uint64_t remove_overflow(uint64_t value) { return value & MAXFORBIT; }

uint64_t plus_next_bit(uint64_t prev_bit, uint64_t next_bit) {
  return prev_bit + (next_bit << 32);
}

unsigned int mult_ten(s21_extended_decimal *extended_decimal) {
  unsigned int overflow = 0;
  s21_extended_decimal temp = *extended_decimal;
  uint64_t res;
  for (int i = 0; i < 7; i++) {
    res = temp.bits[i] * 10 + overflow;
    extended_decimal->bits[i] = remove_overflow(res);
    overflow = get_overflow(res);
  }
  if (overflow) *extended_decimal = temp;
  return overflow;
}

unsigned int div_ten(s21_extended_decimal *extended_decimal) {
  s21_extended_decimal temp = *extended_decimal;
  uint64_t remainder = 0;
  uint64_t res;
  for (int i = 6; i >= 0; i--) {
    res = plus_next_bit(temp.bits[i], remainder);
    extended_decimal->bits[i] = res / 10;
    remainder = res % 10;
  }
  return (unsigned int)remainder;
}

unsigned int add_digit_to_end(s21_extended_decimal *value) {
  unsigned int return_code = 0;
  if (mult_ten(value))
    return_code = 1;
  else
    value->scale += 1;
  return return_code;
}

unsigned int remove_digit_from_end(s21_extended_decimal *value) {
  value->scale -= 1;
  return div_ten(value);
}

s21_extended_decimal convert_to_extended(s21_decimal decimal) {
  s21_extended_decimal extended_decimal = {0};
  extended_decimal.bits[0] = decimal.bits[0];
  extended_decimal.bits[1] = decimal.bits[1];
  extended_decimal.bits[2] = decimal.bits[2];
  extended_decimal.sign = get_sign(decimal);
  extended_decimal.scale = get_scale(decimal);
  return extended_decimal;
}

s21_decimal convert_to_s21_decimal(s21_extended_decimal extended_decimal) {
  s21_decimal decimal = {0};
  for (int i = 0; i < 4; i++) {
    decimal.bits[i] = (unsigned int)extended_decimal.bits[i];
  }
  set_scale(&decimal, extended_decimal.scale);
  set_sign(&decimal, extended_decimal.sign);
  return decimal;
}

void set_null_decimal(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) decimal->bits[i] = 0;
}

//
void set_null_extended_decimal(s21_extended_decimal *value) {
  for (int i = 0; i < 7; i++) value->bits[i] = 0;
  value->sign = 0;
  value->scale = 0;
}

int char_to_num(char ch) { return ch - '0'; }

int bank_rounding(s21_extended_decimal ext_decimal, int remainder,
                  int counter) {
  int plus_one = 0;
  if (remainder > 5) {
    plus_one = 1;
  } else if (remainder == 5) {
    if (counter > 1) {
      plus_one = 1;
    } else if (ext_decimal.bits[0] & 1) {
      plus_one = 1;
    }
  }
  return plus_one;
}

unsigned int add_num(s21_extended_decimal *ext_decimal, int num) {
  unsigned int overflow = num;
  s21_extended_decimal temp = *ext_decimal;
  for (int i = 0; i < 7; ++i) {
    temp.bits[i] += overflow;
    overflow = get_overflow(temp.bits[i]);
    temp.bits[i] = remove_overflow(temp.bits[i]);
  }
  if (overflow == 0) *ext_decimal = temp;
  return overflow;
}

s21_extended_decimal sum_by_bits(s21_extended_decimal ext_val_1,
                                 s21_extended_decimal ext_val_2) {
  s21_extended_decimal result = ext_val_1;
  unsigned int overflow = 0;
  for (int i = 0; i < 7; i++) {
    result.bits[i] += ext_val_2.bits[i] + overflow;
    overflow = get_overflow(result.bits[i]);
    result.bits[i] = remove_overflow(result.bits[i]);
  }
  return result;
}

void sum_ext_bits(s21_extended_decimal *value, uint32_t idx, uint64_t bit1,
                  uint64_t bit2, uint64_t bit3) {
  uint64_t complement[3] = {bit1, bit2, bit3};
  for (int i = 0; i < 3; ++i) {
    if (value->bits[idx] > ULLONG_MAX - complement[i]) {
      value->bits[idx + 1] += MAXFORBIT + 1L;
      value->bits[idx] -= ULLONG_MAX - complement[i] + 1;
    } else {
      value->bits[idx] += complement[i];
    }
  }
}

unsigned int scale_equalization(s21_extended_decimal *value1,
                                s21_extended_decimal *value2) {
  unsigned int flag = 0;
  if (value1->scale != value2->scale) {
    int max_val = (value1->scale > value2->scale) ? 1 : 2;
    s21_extended_decimal *max = (max_val == 1) ? value1 : value2;
    s21_extended_decimal *min = (max_val == 2) ? value1 : value2;
    int exp_dif = max->scale - min->scale;
    for (; exp_dif > 0 && flag == 0; --exp_dif) flag = add_digit_to_end(min);
  }
  return flag;
}

int must_down(s21_extended_decimal value) {
  int flag = 0;
  for (int i = 3; i < 7; ++i) flag |= (value.bits[i] != 0);
  if (flag == 0) flag = value.sign > 28;
  return flag;
}

void remove_trailing_zeroes(s21_extended_decimal *value) {
  if (value->scale > 0) {
    s21_extended_decimal temp = *value;
    int flag = 1;
    int remainder = 0;
    while (flag) {
      if (value->scale > 0) {
        remainder = remove_digit_from_end(&temp);
        if (remainder == 0) {
          *value = temp;
        } else {
          flag = 0;
        }
      } else
        flag = 0;
    }
  }
}

s21_decimal decimal_remove_trailing_zeroes(s21_decimal value) {
  s21_decimal result;
  set_null_decimal(&result);
  if (!is_zero(value)) {
    s21_extended_decimal temp = convert_to_extended(value);
    remove_trailing_zeroes(&temp);
    result = convert_to_s21_decimal(temp);
  }
  return result;
}

int normalize(s21_extended_decimal *value) {
  int overflow = 0;
  unsigned int remainder = 0;
  int counter = 0;
  for (int i = 0; i < 6; ++i) {
    value->bits[i + 1] += get_overflow(value->bits[i]);
    value->bits[i] = remove_overflow(value->bits[i]);
  }
  while (must_down(*value) && value->scale > 0) {
    remainder = remove_digit_from_end(value);
    if (remainder) counter++;
  }
  overflow = must_down(*value);
  if (bank_rounding(*value, remainder, counter) && overflow == 0) {
    if (add_num(value, 1)) overflow = 1;
    if (must_down(*value)) {
      if (value->scale > 0) {
        remove_digit_from_end(value);
        add_num(value, 1);
      } else
        overflow = 1;
    }
  }
  if (!overflow) remove_trailing_zeroes(value);
  return overflow;
}

int compare(s21_extended_decimal ext_val_1, s21_extended_decimal ext_val_2) {
  int return_code = 0;
  for (int i = 6; i >= 0 && return_code == 0; --i) {
    if (ext_val_1.bits[i] != ext_val_2.bits[i])
      return_code = (ext_val_1.bits[i] > ext_val_2.bits[i]) ? 1 : -1;
  }
  return return_code;
}

void invert_bits(s21_extended_decimal *value) {
  for (int i = 0; i < 7; ++i) {
    value->bits[i] = ~value->bits[i];
    value->bits[i] &= MAXFORBIT;
  }
  add_num(value, 1);
}

s21_extended_decimal calculate_bits_diff(s21_extended_decimal value_1,
                                         s21_extended_decimal value_2) {
  s21_extended_decimal result;
  invert_bits(&value_2);
  result = sum_by_bits(value_1, value_2);
  return result;
}

s21_extended_decimal shift_left(s21_extended_decimal value, int shift) {
  s21_extended_decimal res;
  set_null_extended_decimal(&res);
  int numbits = shift / 32;
  shift %= 32;
  for (int i = 7 - 1; i >= numbits; --i) res.bits[i] = value.bits[i - numbits];
  for (int i = 7 - 1; i >= 0; --i) res.bits[i] <<= shift;
  for (int i = 7 - 1; i > 0; --i) res.bits[i] += get_overflow(res.bits[i - 1]);
  for (int i = 7 - 1; i >= 0; --i) res.bits[i] = remove_overflow(res.bits[i]);
  return res;
}

s21_extended_decimal whole_division(s21_extended_decimal v_1,
                                    s21_extended_decimal v_2,
                                    s21_extended_decimal *res) {
  res->scale = 0;
  for (int i = 2; i >= 0; --i) {
    for (int j = 31; j >= 0; --j) {
      s21_extended_decimal tmp = shift_left(v_2, i * 32 + j);
      int comparator = compare(v_1, tmp);
      if (comparator >= 0) {
        res->bits[i] += (uint64_t)1 << j;
        v_1 = calculate_bits_diff(v_1, tmp);
        if (comparator == 0) {
          j = -1;
          i = -1;
        }
      }
    }
  }
  return v_1;
}

void fractional_division(s21_extended_decimal ext_v_1,
                         s21_extended_decimal ext_v_2,
                         s21_extended_decimal *res) {
  unsigned int flag = 0;
  for (int i = 0; i < 28 + 2 && flag == 0; ++i) {
    flag = mult_ten(res);
    if (flag == 0) {
      res->scale += 1;
      mult_ten(&ext_v_1);
      int add = 0;
      for (int j = 3; j >= 0; --j) {
        s21_extended_decimal tmp = shift_left(ext_v_2, j);
        int comparator = compare(ext_v_1, tmp);
        if (comparator >= 0) {
          add += (uint64_t)1 << j;
          ext_v_1 = calculate_bits_diff(ext_v_1, tmp);
          if (comparator == 0) {
            j = -1;
            flag = 1;
          }
        }
      }
      add_num(res, add);
    }
  }
}

int is_ext_zero(s21_extended_decimal value) {
  int result = 1;
  for (int i = 0; i < 7; ++i) result &= (value.bits[i] == 0);
  return result;
}