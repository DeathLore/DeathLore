#ifndef DL_MATRIX_H
#define DL_MATRIX_H

#include <math.h>
#include <stdlib.h>

// Логическая правда
#define SUCCESS 1
// Логическая ложь
#define FAILURE 0
// Ошибок нет
#define OK 0
// Использована неверно созданная матрица
#define INCMATR 1
// Значения матрицы не позволяют вычислить решение
#define CALCERROR 2

typedef struct matrix_struct {
  // A[r][c] = const
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Инициализация матрицы
int DL_create_matrix(int rows, int columns, matrix_t *result);
// Удаление матрицы
void DL_remove_matrix(matrix_t *A);

// Проверка двух матриц на равенство друг другу.
// Возвращает "1", если равны; и "0", если не равны.
int DL_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение матриц.
int DL_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Разность матриц.
int DL_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число (с плавающей запятой).
int DL_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение матриц друг на друга.
int DL_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы.
int DL_transpose(matrix_t *A, matrix_t *result);

// Нахождение алгебраического дополнения матрицы.
int DL_calc_complements(matrix_t *A, matrix_t *result);

// Вычисление определителя(детерминанта).
int DL_determinant(matrix_t *A, double *result);

// Нахождение обратной матрицы.
int DL_inverse_matrix(matrix_t *A, matrix_t *result);

// Проверка, равно ли количество строк и столбцов.
// Возвращает "1", если равно; и "0", если не равно.
int DL_eq_rac(matrix_t const *const A, matrix_t const *const B);
// Побочная функция, которая помогает вычислить минор матрицы.
// Вычисляет матрицу на ранг меньше. Row - строка которую нужно исключить;
// Column - исключаемый столбец.
void DL_pre_minor_calc(matrix_t const *const A, int row, int column,
                       matrix_t *result);
// Побочная для определителя функция, фактически оборачивается функцией
// определителя. Рекурсивно вычисляет определитель матриц малых рангов. Матрицы
// больших рангов вычислить не позволит рекурсивная природа реализации.
double DL_reqursive_det(matrix_t *A);

#endif