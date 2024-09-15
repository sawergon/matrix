#include "test_runner.h"

int main(void) {
  SRunner *sr;

  sr = srunner_create(NULL);
  srunner_add_suite(sr, s21_create_matrix_cases());
  srunner_add_suite(sr, s21_remove_matrix_cases());
  srunner_add_suite(sr, s21_eq_matrix_cases());
  srunner_add_suite(sr, s21_sum_matrix_cases());
  srunner_add_suite(sr, s21_sub_matrix_cases());
  srunner_add_suite(sr, s21_mult_number_cases());
  srunner_add_suite(sr, s21_mult_matrix_cases());
  srunner_add_suite(sr, s21_transpose_cases());
  srunner_add_suite(sr, s21_calc_complements_cases());
  srunner_add_suite(sr, s21_determinant_cases());
  srunner_add_suite(sr, s21_inverse_matrix_cases());

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);

  return 0;
}
