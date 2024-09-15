#include "test_runner.h"

START_TEST(s21_remove_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_03) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_04) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 4, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_matrix_06) {
  int res = 0;
  matrix_t A = {0};

  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(first_null) { s21_remove_matrix(NULL); }
END_TEST

Suite *s21_remove_matrix_cases(void) {
  Suite *s = suite_create("remove_matrix");
  TCase *tc = tcase_create("s21_remove_matrix_cases");

  tcase_add_test(tc, s21_remove_matrix_01);
  tcase_add_test(tc, s21_remove_matrix_02);
  tcase_add_test(tc, s21_remove_matrix_03);
  tcase_add_test(tc, s21_remove_matrix_04);
  tcase_add_test(tc, s21_remove_matrix_05);
  tcase_add_test(tc, s21_remove_matrix_06);

  tcase_add_test(tc, first_null);

  suite_add_tcase(s, tc);
  return s;
}