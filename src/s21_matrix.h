#ifndef C6_S21_MATRIX_1_SRC_S21_MATRIX_H_
#define C6_S21_MATRIX_1_SRC_S21_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @mainpage Реализация типа decimal
 * Данный проект представляет реализацию типа matrix
 * @section s1 Представление типа matrix
 * Тип matrix представляется в виде двумерного массива
 *
 */
/**
 * @file
 * @brief заголовочный файл библиотеки s21_matrix.a
 */
/**
 * тип матрицы
 * matrix  - массив для хранения данных double
 * rows    - кол-во строк
 * columns - кол-во столбцов
 */
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;
/**
 * @addtogroup error_codes Коды ошибок
 * @{
 */
/// успешное выполнение операции
#define OK 0
/// не верный формат матрицы
#define INCORRECT_MATRIX 1
/// ошибка вычислений
#define CALC_ERROR 2
///@}
/**
 * создание типа
 * @param rows кол-во строк
 * @param columns кол-во столбцов
 * @param result указатель на матрицу
 * @return код ошибки @link error_codes
 */
int s21_create_matrix(int rows, int columns, matrix_t *result);
/**
 *
 * @param A
 */
void s21_remove_matrix(matrix_t *A);

/**
 * @addtogroup comparison_res Результат сравнения
 * @{
 */
/// сравнение успешно
#define SUCCESS 1
/// сравнение неуспешно
#define FAILURE 0
///@}

/**
 * сравнение матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @return результат сравнения {@link comparison_res}
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

/**
 * сложение матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @param result результат сложения
 * @return код ошибки {@link error_codes}
 */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
/**
 * разность матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @param result результат разности
 * @return код ошибки {@link error_codes}
 */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * произведение матрицы на число(умножение каждого элемента на число)
 * @param A матрица для умножения
 * @param number число типа double
 * @param result матрица -- результат умножения
 * @return код ошибки {@link error_codes}
 */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
/**
 * умножение матриц
 * @param A первая матрица
 * @param B вторая матрица
 * @param result результат умножения
 * @return код ошибки {@link error_codes}
 */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/**
 * транспонирование матрицы (rows->cols cols->rows)
 * @param A матрица для транспонирования
 * @param result результат транспонирования
 * @return код ошибки {@link error_codes}
 */
int s21_transpose(matrix_t *A, matrix_t *result);

/**
 * подсчет матрицы миноров
 * @param A исходная матрица
 * @param result матрица миноров
 * @return код ошибки {@link error_codes}
 */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/**
 * вычисление определителя матрицы
 * @param A исходная матрица
 * @param result значение определителя
 * @return код ошибки {@link error_codes}
 */
int s21_determinant(matrix_t *A, double *result);

/**
 * вычисление обратной матрицы
 * @details вычисление методом нахождения матрицы миноров
 * #TODO попробовать метод s21_LU разложения. в перспективе быстрее
 * @param A исходная матрица
 * @param result обратная матрица
 * @return код ошибки {@link error_codes}
 */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/**
 * проверка матрицы на правильность заполнения
 * кол-во строк и столбцов > 0
 * указатель на массив не пуст
 * @param matrix исходная матрица
 * @return результат проверки bool
 */
bool s21_is_correct_matrix(matrix_t *matrix);

/**
 * вывод матрицы на экран
 * @param matrix исходная матрица
 */
void s21_print_matrix(matrix_t *matrix);

/**
 * получение минора к i, j элементу
 * @param matrix исходная матрица
 * @param result результирующая матрица
 * @param i
 * @param j
 * @param size размер входной матрицы
 */
void s21_get_minor(matrix_t *matrix, matrix_t *result, int i, int j, int size);
#endif  // C6_S21_MATRIX_1_SRC_S21_MATRIX_H_
