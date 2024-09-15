#include "test_runner.h"

START_TEST(mult_matrix) {
  int rows = rand() % 5 + 1;
  int cols = rand() % 5 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = get_rand(-10e10, 10e10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = get_rand(-10e10, 10e10);

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);

  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < mtx.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < m.columns; k++)
        check.matrix[i][j] += m.matrix[i][k] * mtx.matrix[k][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

START_TEST(simple_mult) {
  const int rows = 2;
  const int cols = 3;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) mtx.matrix[i][j] = c++;

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 58;
  check.matrix[0][1] = 64;
  check.matrix[1][0] = 139;
  check.matrix[1][1] = 154;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(dif_size) {
  matrix_t B = {};
  matrix_t A = {};
  matrix_t C = {};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  int res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(first_null) {
  matrix_t B = {};
  matrix_t C = {};
  s21_create_matrix(2, 2, &B);
  int res = s21_mult_matrix(NULL, &B, &C);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(second_null) {
  matrix_t A = {};
  matrix_t C = {};
  s21_create_matrix(2, 1, &A);
  int res = s21_mult_matrix(&A, NULL, &C);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(therd_null) {
  matrix_t B = {};
  matrix_t A = {};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  int res = s21_mult_matrix(&A, &B, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_mult_matrix_cases(void) {
  Suite *s = suite_create("mult_matrix");
  TCase *tc = tcase_create("case_mult_matrix");

  tcase_add_test(tc, dif_size);
  tcase_add_test(tc, first_null);
  tcase_add_test(tc, second_null);
  tcase_add_test(tc, therd_null);

  tcase_add_loop_test(tc, mult_matrix, 0, 100);
  tcase_add_test(tc, simple_mult);

  suite_add_tcase(s, tc);
  return s;
}