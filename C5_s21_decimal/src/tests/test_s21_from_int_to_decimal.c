#include "tests.h"

START_TEST(test_from_int_to_decimal_ok1) {
  // степень 29 (допустимое значение от 0 до 28)
  s21_decimal dec_check = {0};
  int num = 1;
  s21_from_int_to_decimal(num, &dec_check);
  ck_assert_int_eq(dec_check.bits[0], num);
}

START_TEST(test_from_int_to_decimal_ok2) {
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal dec_check = {0};
  int num = -2147483647;
  int tmp = 0;
  s21_from_int_to_decimal(num, &dec_check);
  s21_from_decimal_to_int(dec_check, &tmp);
  ck_assert_int_eq(tmp, num);
}

START_TEST(test_from_int_to_decimal_ok3) {
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal dec_check = {0};
  int num = 0;
  int tmp = 1;
  s21_from_int_to_decimal(num, &dec_check);
  s21_from_decimal_to_int(dec_check, &tmp);
  ck_assert_int_eq(tmp, num);
}

START_TEST(test_from_int_to_decimal_ok4) {
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal dec_check = {0};
  int num = 2147483647;
  int tmp = 0;
  s21_from_int_to_decimal(num, &dec_check);
  s21_from_decimal_to_int(dec_check, &tmp);
  ck_assert_int_eq(tmp, num);
}

START_TEST(test_from_int_to_decimal_ok5) {
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal dec_check = {0};
  int num = -1;
  int tmp = 0;
  s21_from_int_to_decimal(num, &dec_check);
  s21_from_decimal_to_int(dec_check, &tmp);
  ck_assert_int_eq(tmp, num);
}

Suite *suite_int_to_decimal(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("from_int_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_from_int_to_decimal_ok1);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok2);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok3);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok4);
  tcase_add_test(tc_core, test_from_int_to_decimal_ok5);

  suite_add_tcase(s, tc_core);

  return s;
}
