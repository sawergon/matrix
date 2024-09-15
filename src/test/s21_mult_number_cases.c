#include "test_runner.h"
START_TEST(null) {
  matrix_t result = {};
  double number = 4;
  ck_assert_int_eq(s21_mult_number(NULL, number, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(mult_number_1) {
  matrix_t A = {};
  double number = 3.14;
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  double number = 3;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  double number = 3;
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; ++i) {
    for (int j = 0; j < A.columns; ++j) {
      A.matrix[i][j] = (i + j);
    }
  }
  s21_create_matrix(3, 3, &eq_matrix);
  for (int i = 0; i < A.rows; ++i) {
    for (int j = 0; j < A.columns; ++j) {
      eq_matrix.matrix[i][j] = (i + j) * number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST
Suite *s21_mult_number_cases(void) {
  Suite *s = suite_create("mult_number");
  TCase *tc = tcase_create("case_mult_number");

  tcase_add_test(tc, null);
  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_2);
  tcase_add_test(tc, mult_number_3);

  suite_add_tcase(s, tc);
  return s;
}