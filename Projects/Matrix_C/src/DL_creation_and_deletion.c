#include "DL_matrix.h"

int DL_create_matrix(int rows, int columns, matrix_t *result) {
  // Реализация через строки указателей на столбцы указателей на значение

  int ret_error = OK;

  if (rows > 0 && columns > 0 && NULL != result) {
    result->columns = columns;
    result->rows = rows;

    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
  } else
    ret_error = INCMATR;

  return ret_error;
}

void DL_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++)
      if (A->matrix[i]) free(A->matrix[i]);
    free(A->matrix);
    A->matrix = NULL;
  }

  A->columns = 0;
  A->rows = 0;
}
