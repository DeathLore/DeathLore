#include "DL_matrix.h"

void DL_pre_minor_calc(matrix_t const *const A, int row, int column,
                       matrix_t *const result) {
  // Формирует матрицу размером на 1 и 1 меньше, чем A;
  // заполняет содержимым матр. A, за исклбчением указанного строки и столбца.
  DL_create_matrix(A->rows - 1, A->columns - 1, result);

  for (int i = 0, res_rows = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0, res_columns = 0; j < A->columns; j++) {
        if (j != column) {
          result->matrix[res_rows][res_columns] = A->matrix[i][j];
          res_columns += 1;
        }
      }
      res_rows += 1;
    }
  }
}

double DL_reqursive_det(matrix_t *A) {
  double ret_val = 0.0;
  if (A->rows == 2)
    // Вырожденный случай для ранга "2" матрицы
    ret_val =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else if (A->rows == 1)
    // Вырожденный случай для ранга "1"
    ret_val = A->matrix[0][0];
  else {
    // Рекурсивное вычисление определителя через постоянное уменьшение ранга.
    for (int j = 0; j < A->columns; j++) {
      matrix_t buf_matr;
      DL_pre_minor_calc(A, 0, j, &buf_matr);
      if ((j + 1) % 2 == 1)
        ret_val += A->matrix[0][j] * DL_reqursive_det(&buf_matr);
      else
        ret_val -= A->matrix[0][j] * DL_reqursive_det(&buf_matr);
      DL_remove_matrix(&buf_matr);
    }
  }

  return ret_val;
}

int DL_determinant(matrix_t *A, double *result) {
  // Обёртка над DL_reqursive_det
  int ret_error = 0;
  *result = 0.0;

  if (A->matrix == NULL)
    ret_error = INCMATR;
  else if (A->rows == A->columns) {
    *result = DL_reqursive_det(A);
  } else
    ret_error = CALCERROR;

  return ret_error;
}

double DL_minor(matrix_t *A, int i, int j) {
  double ret_val = 0.0;
  matrix_t buf_matr;
  DL_pre_minor_calc(A, i, j, &buf_matr);

  DL_determinant(&buf_matr, &ret_val);

  DL_remove_matrix(&buf_matr);

  return ret_val;
}

int DL_calc_complements(matrix_t *A, matrix_t *result) {
  int ret_error = 0;

  if (A->matrix == NULL)
    ret_error = INCMATR;
  else if (A->rows == A->columns) {
    DL_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        if ((i + j) % 2 == 0)
          result->matrix[i][j] = DL_minor(A, i, j);
        else
          result->matrix[i][j] = -1 * DL_minor(A, i, j);
      }
    }
  } else
    ret_error = CALCERROR;

  return ret_error;
}

int DL_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret_error = OK;

  if (A->matrix == NULL || A->rows < 1 || A->columns < 1)
    ret_error = INCMATR;
  else if (A->rows == A->columns) {
    DL_create_matrix(A->rows, A->columns, result);
    double A_det = 0.0;
    int det_check = DL_determinant(A, &A_det);

    if (det_check == 0 && A_det != 0 && A->rows != 1) {
      matrix_t buf_matr_comp, buf_matr_trans_comp;

      DL_calc_complements(A, &buf_matr_comp);
      DL_transpose(&buf_matr_comp, &buf_matr_trans_comp);
      DL_remove_matrix(&buf_matr_comp);

      DL_mult_number(&buf_matr_trans_comp, 1 / A_det, result);
      DL_remove_matrix(&buf_matr_trans_comp);
    } else if (det_check == 0 && A_det != 0)
      result->matrix[0][0] = 1 / A_det;
    else
      ret_error = CALCERROR;
  } else
    ret_error = CALCERROR;

  return ret_error;
}
