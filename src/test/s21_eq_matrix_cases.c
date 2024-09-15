#include "test_runner.h"
START_TEST(zero_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, result);
}
END_TEST

START_TEST(different_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 5;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size + 1, size + 1, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(first_zero) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 5;
  s21_create_matrix(size, size, &A);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(second_zero) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 5;
  s21_create_matrix(size + 1, size + 1, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(FAILURE, result);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(null) {
  int result = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(FAILURE, result);
}
END_TEST

START_TEST(eq_01) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 5;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, result);
  s21_remove_matrix(&B);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_02) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 30;
  s21_create_matrix(size, size, &A);
  s21_create_matrix(size, size, &B);
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, result);
  s21_remove_matrix(&B);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_03) {
  matrix_t A = {0};
  matrix_t B = {0};
  int size = 5;
  s21_create_matrix(size, size, &A);
  A.matrix[0][1] = 237.5678;
  s21_create_matrix(size, size, &B);
  B.matrix[0][1] = 237.5678;
  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(SUCCESS, result);
  s21_remove_matrix(&B);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(dif_cols) {
  matrix_t B = {};
  matrix_t A = {};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(not_eq) {
  matrix_t B = {};
  matrix_t A = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  B.matrix[0][1] = 1;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_eq_matrix_cases(void) {
  Suite *s = suite_create("eq_matrix");
  TCase *tc = tcase_create("case_eq_matrix");

  tcase_add_test(tc, zero_matrix);
  tcase_add_test(tc, different_size);
  tcase_add_test(tc, first_zero);
  tcase_add_test(tc, second_zero);
  tcase_add_test(tc, null);
  tcase_add_test(tc, eq_01);
  tcase_add_test(tc, eq_02);
  tcase_add_test(tc, eq_03);

  tcase_add_test(tc, not_eq);
  tcase_add_test(tc, dif_cols);

  suite_add_tcase(s, tc);
  return s;
}