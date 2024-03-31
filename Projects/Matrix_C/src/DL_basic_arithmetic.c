#include "DL_matrix.h"

int DL_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_error = OK;

  if (!A || !B || !A->matrix || !B->matrix)
    ret_error = INCMATR;
  else if (DL_eq_rac(A, B)) {
    DL_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  } else
    ret_error = CALCERROR;

  return ret_error;
}

int DL_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_error = OK;

  if (!A || !B || !A->matrix || !B->matrix)
    ret_error = INCMATR;
  else if (DL_eq_rac(A, B)) {
    DL_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  } else
    ret_error = CALCERROR;

  return ret_error;
}

int DL_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret_error = OK;

  if (!A || !A->matrix)
    ret_error = INCMATR;
  else {
    DL_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return ret_error;
}

int DL_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_error = OK;

  if (!A || !B || !A->matrix || !B->matrix)
    ret_error = INCMATR;
  else if (A->columns == B->rows) {
    DL_create_matrix(A->rows, B->columns, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  } else
    ret_error = CALCERROR;

  return ret_error;
}

int DL_transpose(matrix_t *A, matrix_t *result) {
  int ret_error = 0;

  if (!A || !A->matrix)
    ret_error = INCMATR;
  else {
    DL_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return ret_error;
}
