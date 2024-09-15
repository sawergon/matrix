#include "test_runner.h"

START_TEST(s21_create_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_03) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_04) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 4, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(10, 15, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_06) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_07) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_08) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_09) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(-1, 1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(third_null) {
  int res = 0;
  res = s21_create_matrix(1, 1, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

Suite *s21_create_matrix_cases(void) {
  Suite *s = suite_create("\n create_matrix");
  TCase *tc = tcase_create("s21_create_matrix_cases");

  tcase_add_test(tc, s21_create_matrix_01);
  tcase_add_test(tc, s21_create_matrix_02);
  tcase_add_test(tc, s21_create_matrix_03);
  tcase_add_test(tc, s21_create_matrix_04);
  tcase_add_test(tc, s21_create_matrix_05);
  tcase_add_test(tc, s21_create_matrix_06);
  tcase_add_test(tc, s21_create_matrix_07);
  tcase_add_test(tc, s21_create_matrix_08);
  tcase_add_test(tc, s21_create_matrix_09);

  tcase_add_test(tc, third_null);

  suite_add_tcase(s, tc);
  return s;
}
