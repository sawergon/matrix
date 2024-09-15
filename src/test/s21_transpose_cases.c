#include "test_runner.h"

START_TEST(transpose_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);

  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double rand_val = get_rand(-10e10, 10e10);
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(second_null) {
  matrix_t A = {};
  s21_create_matrix(2, 1, &A);
  int res = s21_transpose(&A, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(first_null) {
  matrix_t C = {};
  int res = s21_transpose(NULL, &C);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

Suite *s21_transpose_cases(void) {
  Suite *s = suite_create("transpose");
  TCase *tc = tcase_create("case_transpose_matrix");

  tcase_add_loop_test(tc, transpose_matrix, 0, 100);

  tcase_add_test(tc, first_null);
  tcase_add_test(tc, second_null);

  suite_add_tcase(s, tc);
  return s;
}