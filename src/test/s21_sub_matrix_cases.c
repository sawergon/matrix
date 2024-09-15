#include "test_runner.h"
START_TEST(sub_matrix_01) {
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_02) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(5, 5, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_03) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t check = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; ++i) {
    A.matrix[1][i] = 1;
    check.matrix[1][i] = 1;
  }
  for (int i = 0; i < B.rows; ++i) {
    B.matrix[i][1] = 1;
    check.matrix[i][1] = -1;
  }
  check.matrix[1][1] = 0;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_04) {
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t check = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &check);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  B.matrix[0][0] = 9;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 7;
  B.matrix[1][0] = 6;
  B.matrix[1][1] = 5;
  B.matrix[1][2] = 4;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 2;
  B.matrix[2][2] = 1;

  double val = -8;
  for (int i = 0; i < check.rows; ++i) {
    for (int j = 0; j < check.columns; ++j) {
      check.matrix[i][j] = val;
      val += 2;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(dif_cols) {
  matrix_t B = {};
  matrix_t A = {};
  matrix_t C = {};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  int res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(third_null) {
  matrix_t B = {};
  matrix_t A = {};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  int res = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(second_null) {
  matrix_t A = {};
  matrix_t C = {};
  s21_create_matrix(2, 1, &A);
  int res = s21_sub_matrix(&A, NULL, &C);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_sub_matrix_cases(void) {
  Suite *s = suite_create("sub_matrix");
  TCase *tc = tcase_create("case_sub_matrix");

  tcase_add_test(tc, sub_matrix_01);
  tcase_add_test(tc, sub_matrix_02);
  tcase_add_test(tc, sub_matrix_03);
  tcase_add_test(tc, sub_matrix_04);

  tcase_add_test(tc, dif_cols);
  tcase_add_test(tc, second_null);
  tcase_add_test(tc, third_null);

  suite_add_tcase(s, tc);
  return s;
}