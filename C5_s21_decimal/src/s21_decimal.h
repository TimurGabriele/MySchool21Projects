#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define SCALE_MASK 0x00FF0000
#define SCALE_SHIFT 16
#define MAXFORBIT 0xFFFFFFFF

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  uint64_t bits[7];
  int sign;
  int scale;
} s21_extended_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int get_bit(unsigned int value, int idx);
void set_bit(unsigned int *num, int idx, int value);
int get_sign(s21_decimal decimal);
void set_sign(s21_decimal *decimal, int sign);
int is_zero(s21_decimal decimal);
int get_scale(s21_decimal decimal);
void set_scale(s21_decimal *decimal, int scale);
int char_to_num(char c);
unsigned int get_overflow(uint64_t value);
uint64_t plus_next_bit(uint64_t prev_bit, uint64_t next_bit);
uint64_t remove_overflow(uint64_t res);
unsigned int mult_ten(s21_extended_decimal *extended_decimal);
unsigned int div_ten(s21_extended_decimal *extended_decimal);
unsigned int add_digit_to_end(s21_extended_decimal *value);
unsigned int remove_digit_from_end(s21_extended_decimal *value);
int is_correct_decimal(s21_decimal decimal);
void set_null_decimal(s21_decimal *decimal);
void set_null_extended_decimal(s21_extended_decimal *value);
s21_extended_decimal convert_to_extended(s21_decimal decimal);
s21_decimal convert_to_s21_decimal(s21_extended_decimal extended_decimal);
int bank_rounding(s21_extended_decimal ext_decimal, int remainder, int counter);
unsigned int add_num(s21_extended_decimal *ext_decimal, int num);
s21_extended_decimal sum_by_bits(s21_extended_decimal value1,
                                 s21_extended_decimal value2);
void sum_ext_bits(s21_extended_decimal *value, uint32_t index, uint64_t add1,
                  uint64_t add2, uint64_t add3);
unsigned int scale_equalization(s21_extended_decimal *value1,
                                s21_extended_decimal *value2);
int must_down(s21_extended_decimal value);
void remove_trailing_zeroes(s21_extended_decimal *value);
s21_decimal decimal_remove_trailing_zeroes(s21_decimal value);
int normalize(s21_extended_decimal *value);
int compare(s21_extended_decimal value_1, s21_extended_decimal value_2);
void invert_bits(s21_extended_decimal *value);
s21_extended_decimal calculate_bits_diff(s21_extended_decimal value_1,
                                         s21_extended_decimal value_2);
s21_extended_decimal shift_left(s21_extended_decimal value, int shift);
s21_extended_decimal whole_division(s21_extended_decimal v_1,
                                    s21_extended_decimal v_2,
                                    s21_extended_decimal *res);

void fractional_division(s21_extended_decimal v_1, s21_extended_decimal v_2,
                         s21_extended_decimal *res);
int is_ext_zero(s21_extended_decimal value);

void print_decimal(s21_decimal num);
#endif