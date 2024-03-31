#include "DL_matrix.h"

int DL_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret_val = FAILURE;

  if (DL_eq_rac(A, B)) {
    int buf_cmp_res = SUCCESS;

    for (int i = 0; i < A->rows && buf_cmp_res; i++) {
      for (int j = 0; j < A->columns && buf_cmp_res; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1E-7)
          buf_cmp_res = FAILURE;
      }
    }

    ret_val = buf_cmp_res;
  }

  return ret_val;
}

int DL_eq_rac(matrix_t const *const A, matrix_t const *const B) {
  int ret_val = FAILURE;

  if (A->rows == B->rows && A->columns == B->columns) ret_val = SUCCESS;

  return ret_val;
}
