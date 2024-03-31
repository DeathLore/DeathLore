#include <check.h>

#include "DL_matrix.h"

#define OK 0
#define ERROR_INIT 1
#define ERROR_CALC 2
#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308

void DL_init_matrix(double number, matrix_t *A) {
  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->columns; number += 1.0, y += 1)
      A->matrix[x][y] = number;
  }
}

START_TEST(DL_create_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(1, 1, &A);
  ck_assert_int_eq(res, OK);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_create_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(2, 2, &A);
  ck_assert_int_eq(res, OK);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_create_matrix_03) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(3, 2, &A);
  ck_assert_int_eq(res, OK);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_create_matrix_04) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(2, 4, &A);
  ck_assert_int_eq(res, OK);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_create_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(10, 15, &A);
  ck_assert_int_eq(res, OK);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_create_matrix_06) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(0, 0, &A);
  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_create_matrix_07) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(1, 0, &A);
  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_create_matrix_08) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(0, 1, &A);
  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_create_matrix_09) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(-1, 1, &A);
  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_remove_matrix_01) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(2, 2, &A);
  DL_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(DL_remove_matrix_02) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(1, 1, &A);
  DL_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(DL_remove_matrix_03) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(3, 2, &A);
  DL_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(DL_remove_matrix_04) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(3, 4, &A);
  DL_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(DL_remove_matrix_05) {
  int res = 0;
  matrix_t A = {0};

  res = DL_create_matrix(3, 2, &A);
  DL_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(DL_eq_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 2, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(3, 2, &B);
  DL_init_matrix(1.0, &B);

  res = DL_eq_matrix(&A, &B);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_eq_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 2, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(3, 2, &B);
  DL_init_matrix(2.0, &B);

  res = DL_eq_matrix(&B, &A);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(DL_eq_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 4, &A);
  DL_init_matrix(-5.0, &A);

  DL_create_matrix(3, 4, &B);
  DL_init_matrix(1.0, &B);

  res = DL_eq_matrix(&A, &B);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(DL_eq_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 2, &A);
  DL_init_matrix(10.0, &A);

  DL_create_matrix(3, 2, &B);
  DL_init_matrix(-10.0, &B);

  res = DL_eq_matrix(&A, &B);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(DL_eq_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 2, &A);
  DL_init_matrix(1.0, &A);
  DL_create_matrix(3, 3, &B);
  DL_init_matrix(1.0, &B);
  res = DL_eq_matrix(&A, &B);
  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(DL_eq_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(10, 10, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(10, 10, &B);
  DL_init_matrix(1.0, &B);

  res = DL_eq_matrix(&A, &B);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(1.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(0.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(2.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(-3.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(5.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(5.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(-3.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 6.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 10.0;
  X.matrix[1][1] = 12.0;
  X.matrix[1][2] = 14.0;
  X.matrix[1][3] = 16.0;
  X.matrix[2][0] = 18.0;
  X.matrix[2][1] = 20.0;
  X.matrix[2][2] = 22.0;
  X.matrix[2][3] = 24.0;
  X.matrix[3][0] = 26.0;
  X.matrix[3][1] = 28.0;
  X.matrix[3][2] = 30.0;
  X.matrix[3][3] = 32.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(1.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 8.0;
  X.matrix[2][0] = 10.0;
  X.matrix[2][1] = 12.0;
  X.matrix[3][0] = 14.0;
  X.matrix[3][1] = 16.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(-1.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(3.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 8.0;
  X.matrix[2][0] = 10.0;
  X.matrix[2][1] = 12.0;
  X.matrix[3][0] = 14.0;
  X.matrix[3][1] = 16.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_07) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(4.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(-2.0, &B);

  DL_sum_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 2.0;
  X.matrix[0][1] = 4.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 8.0;
  X.matrix[2][0] = 10.0;
  X.matrix[2][1] = 12.0;
  X.matrix[3][0] = 14.0;
  X.matrix[3][1] = 16.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sum_matrix_08) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  DL_create_matrix(4, 2, &A);

  DL_create_matrix(4, 3, &B);

  res = DL_sum_matrix(&A, &B, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(DL_sum_matrix_09) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  DL_create_matrix(4, 3, &B);

  res = DL_sum_matrix(&A, &B, &Z);

  DL_remove_matrix(&B);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_sub_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(1.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = 0.0;
  X.matrix[1][1] = 0.0;
  X.matrix[1][2] = 0.0;
  X.matrix[1][3] = 0.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 0.0;
  X.matrix[2][2] = 0.0;
  X.matrix[2][3] = 0.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 0.0;
  X.matrix[3][2] = 0.0;
  X.matrix[3][3] = 0.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(0.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(2.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2.0;
  X.matrix[0][1] = -2.0;
  X.matrix[0][2] = -2.0;
  X.matrix[0][3] = -2.0;
  X.matrix[1][0] = -2.0;
  X.matrix[1][1] = -2.0;
  X.matrix[1][2] = -2.0;
  X.matrix[1][3] = -2.0;
  X.matrix[2][0] = -2.0;
  X.matrix[2][1] = -2.0;
  X.matrix[2][2] = -2.0;
  X.matrix[2][3] = -2.0;
  X.matrix[3][0] = -2.0;
  X.matrix[3][1] = -2.0;
  X.matrix[3][2] = -2.0;
  X.matrix[3][3] = -2.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(-3.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(5.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = -8.0;
  X.matrix[0][1] = -8.0;
  X.matrix[0][2] = -8.0;
  X.matrix[0][3] = -8.0;
  X.matrix[1][0] = -8.0;
  X.matrix[1][1] = -8.0;
  X.matrix[1][2] = -8.0;
  X.matrix[1][3] = -8.0;
  X.matrix[2][0] = -8.0;
  X.matrix[2][1] = -8.0;
  X.matrix[2][2] = -8.0;
  X.matrix[2][3] = -8.0;
  X.matrix[3][0] = -8.0;
  X.matrix[3][1] = -8.0;
  X.matrix[3][2] = -8.0;
  X.matrix[3][3] = -8.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(5.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(-3.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 8.0;
  X.matrix[0][1] = 8.0;
  X.matrix[0][2] = 8.0;
  X.matrix[0][3] = 8.0;
  X.matrix[1][0] = 8.0;
  X.matrix[1][1] = 8.0;
  X.matrix[1][2] = 8.0;
  X.matrix[1][3] = 8.0;
  X.matrix[2][0] = 8.0;
  X.matrix[2][1] = 8.0;
  X.matrix[2][2] = 8.0;
  X.matrix[2][3] = 8.0;
  X.matrix[3][0] = 8.0;
  X.matrix[3][1] = 8.0;
  X.matrix[3][2] = 8.0;
  X.matrix[3][3] = 8.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(1.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 0.0;
  X.matrix[1][0] = 0.0;
  X.matrix[1][1] = 0.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 0.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 0.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(-1.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(3.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = -4.0;
  X.matrix[0][1] = -4.0;
  X.matrix[1][0] = -4.0;
  X.matrix[1][1] = -4.0;
  X.matrix[2][0] = -4.0;
  X.matrix[2][1] = -4.0;
  X.matrix[3][0] = -4.0;
  X.matrix[3][1] = -4.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_07) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(4.0, &A);

  DL_create_matrix(4, 2, &B);
  DL_init_matrix(-2.0, &B);

  DL_sub_matrix(&A, &B, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 6.0;
  X.matrix[0][1] = 6.0;
  X.matrix[1][0] = 6.0;
  X.matrix[1][1] = 6.0;
  X.matrix[2][0] = 6.0;
  X.matrix[2][1] = 6.0;
  X.matrix[3][0] = 6.0;
  X.matrix[3][1] = 6.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_sub_matrix_08) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  DL_create_matrix(4, 2, &A);

  DL_create_matrix(4, 3, &B);

  res = DL_sub_matrix(&A, &B, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(DL_sub_matrix_09) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  DL_create_matrix(4, 3, &B);

  res = DL_sub_matrix(&A, &B, &Z);
  DL_remove_matrix(&B);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_mult_number_01) {
  int res = 0;
  double number = 3.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);

  DL_init_matrix(1.0, &A);

  DL_mult_number(&A, number, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 3.0;
  X.matrix[0][1] = 6.0;
  X.matrix[0][2] = 9.0;
  X.matrix[0][3] = 12.0;
  X.matrix[1][0] = 15.0;
  X.matrix[1][1] = 18.0;
  X.matrix[1][2] = 21.0;
  X.matrix[1][3] = 24.0;
  X.matrix[2][0] = 27.0;
  X.matrix[2][1] = 30.0;
  X.matrix[2][2] = 33.0;
  X.matrix[2][3] = 36.0;
  X.matrix[3][0] = 39.0;
  X.matrix[3][1] = 42.0;
  X.matrix[3][2] = 45.0;
  X.matrix[3][3] = 48.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_number_02) {
  int res = 0;
  double number = 5.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(1.0, &A);

  DL_mult_number(&A, number, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 5.0;
  X.matrix[0][1] = 10.0;
  X.matrix[0][2] = 15.0;
  X.matrix[0][3] = 20.0;
  X.matrix[1][0] = 25.0;
  X.matrix[1][1] = 30.0;
  X.matrix[1][2] = 35.0;
  X.matrix[1][3] = 40.0;
  X.matrix[2][0] = 45.0;
  X.matrix[2][1] = 50.0;
  X.matrix[2][2] = 55.0;
  X.matrix[2][3] = 60.0;
  X.matrix[3][0] = 65.0;
  X.matrix[3][1] = 70.0;
  X.matrix[3][2] = 75.0;
  X.matrix[3][3] = 80.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_number_03) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(2.0, &A);

  DL_mult_number(&A, number, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = 4.0;
  X.matrix[0][1] = 6.0;
  X.matrix[1][0] = 8.0;
  X.matrix[1][1] = 10.0;
  X.matrix[2][0] = 12.0;
  X.matrix[2][1] = 14.0;
  X.matrix[3][0] = 16.0;
  X.matrix[3][1] = 18.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_number_04) {
  int res = 0;
  double number = -2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(2.0, &A);

  DL_mult_number(&A, number, &Z);

  DL_create_matrix(4, 2, &X);

  X.matrix[0][0] = -4.0;
  X.matrix[0][1] = -6.0;
  X.matrix[1][0] = -8.0;
  X.matrix[1][1] = -10.0;
  X.matrix[2][0] = -12.0;
  X.matrix[2][1] = -14.0;
  X.matrix[3][0] = -16.0;
  X.matrix[3][1] = -18.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_number_05) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(1, 1, &A);
  DL_init_matrix(2.0, &A);

  DL_mult_number(&A, number, &Z);

  DL_create_matrix(1, 1, &X);

  X.matrix[0][0] = 4.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_number_06) {
  int res = 0;
  double number = 2.0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(0, 0, &A);

  res = DL_mult_number(&A, number, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_mult_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(1.0, &B);

  DL_mult_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 90.0;
  X.matrix[0][1] = 100.0;
  X.matrix[0][2] = 110.0;
  X.matrix[0][3] = 120.0;
  X.matrix[1][0] = 202.0;
  X.matrix[1][1] = 228.0;
  X.matrix[1][2] = 254.0;
  X.matrix[1][3] = 280.0;
  X.matrix[2][0] = 314.0;
  X.matrix[2][1] = 356.0;
  X.matrix[2][2] = 398.0;
  X.matrix[2][3] = 440.0;
  X.matrix[3][0] = 426.0;
  X.matrix[3][1] = 484.0;
  X.matrix[3][2] = 542.0;
  X.matrix[3][3] = 600.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_matrix_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(1.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(-5.0, &B);

  DL_mult_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 30.0;
  X.matrix[0][1] = 40.0;
  X.matrix[0][2] = 50.0;
  X.matrix[0][3] = 60.0;
  X.matrix[1][0] = 46.0;
  X.matrix[1][1] = 72.0;
  X.matrix[1][2] = 98.0;
  X.matrix[1][3] = 124.0;
  X.matrix[2][0] = 62.0;
  X.matrix[2][1] = 104.0;
  X.matrix[2][2] = 146.0;
  X.matrix[2][3] = 188.0;
  X.matrix[3][0] = 78.0;
  X.matrix[3][1] = 136.0;
  X.matrix[3][2] = 194.0;
  X.matrix[3][3] = 252.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  DL_init_matrix(-5.0, &A);

  DL_create_matrix(4, 4, &B);
  DL_init_matrix(1.0, &B);

  DL_mult_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = -78.0;
  X.matrix[0][1] = -92.0;
  X.matrix[0][2] = -106.0;
  X.matrix[0][3] = -120.0;
  X.matrix[1][0] = 34.0;
  X.matrix[1][1] = 36.0;
  X.matrix[1][2] = 38.0;
  X.matrix[1][3] = 40.0;
  X.matrix[2][0] = 146.0;
  X.matrix[2][1] = 164.0;
  X.matrix[2][2] = 182.0;
  X.matrix[2][3] = 200.0;
  X.matrix[3][0] = 258.0;
  X.matrix[3][1] = 292.0;
  X.matrix[3][2] = 326.0;
  X.matrix[3][3] = 360.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 2, &A);
  DL_init_matrix(-5.0, &A);

  DL_create_matrix(2, 4, &B);
  DL_init_matrix(1.0, &B);

  DL_mult_matrix(&A, &B, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = -25.0;
  X.matrix[0][1] = -34.0;
  X.matrix[0][2] = -43.0;
  X.matrix[0][3] = -52.0;
  X.matrix[1][0] = -13.0;
  X.matrix[1][1] = -18.0;
  X.matrix[1][2] = -23.0;
  X.matrix[1][3] = -28.0;
  X.matrix[2][0] = -1.0;
  X.matrix[2][1] = -2.0;
  X.matrix[2][2] = -3.0;
  X.matrix[2][3] = -4.0;
  X.matrix[3][0] = 11.0;
  X.matrix[3][1] = 14.0;
  X.matrix[3][2] = 17.0;
  X.matrix[3][3] = 20.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(1, 1, &A);
  DL_init_matrix(-5.0, &A);

  DL_create_matrix(1, 1, &B);
  DL_init_matrix(1.0, &B);

  DL_mult_matrix(&A, &B, &Z);

  DL_create_matrix(1, 1, &X);

  X.matrix[0][0] = -5.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_mult_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  res = DL_mult_matrix(&A, &B, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_mult_matrix_07) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t Z = {0};

  DL_create_matrix(2, 3, &A);
  DL_init_matrix(-5.0, &A);

  DL_create_matrix(2, 2, &B);
  DL_init_matrix(1.0, &B);

  res = DL_mult_matrix(&A, &B, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(DL_transpose_01) {
  int res = 0;
  matrix_t A = {0};

  res = DL_transpose(&A, &A);
  ck_assert_int_eq(res, ERROR_INIT);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_transpose_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  DL_create_matrix(3, 4, &A);
  DL_init_matrix(1.0, &A);
  res = DL_transpose(&A, &B);
  res = DL_eq_matrix(&A, &B);

  DL_remove_matrix(&A);
  DL_remove_matrix(&B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(DL_transpose_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t T = {0};
  matrix_t B = {0};

  DL_create_matrix(2, 3, &A);
  DL_init_matrix(1.0, &A);
  DL_create_matrix(3, 2, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 4.0;
  B.matrix[1][0] = 2.0;
  B.matrix[1][1] = 5.0;
  B.matrix[2][0] = 3.0;
  B.matrix[2][1] = 6.0;

  res = DL_transpose(&A, &T);
  res = DL_eq_matrix(&T, &B);
  ck_assert_int_eq(res, SUCCESS);
  DL_remove_matrix(&A);
  DL_remove_matrix(&T);
  DL_remove_matrix(&B);
}
END_TEST

START_TEST(DL_determinant_01) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {NULL, 0, 0};

  res = DL_determinant(&A, &determ);
  ck_assert_int_eq(res, ERROR_INIT);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_determinant_02) {
  int res = 0;
  double determ = 0.0;
  matrix_t A = {0};
  DL_create_matrix(1, 2, &A);

  res = DL_determinant(&A, &determ);
  ck_assert_int_eq(res, ERROR_CALC);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_determinant_03) {
  double determ = 0.0;
  matrix_t A = {0};

  DL_create_matrix(1, 1, &A);
  DL_init_matrix(1.0, &A);

  DL_determinant(&A, &determ);
  ck_assert_double_eq(determ, 1.0);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_determinant_04) {
  double determ = 0.0;
  matrix_t A = {0};

  DL_create_matrix(3, 3, &A);
  A.matrix[0][0] = 4000.87;
  A.matrix[0][1] = 454.0;
  A.matrix[0][2] = 4.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = 1.897;
  A.matrix[1][2] = 3.0;
  A.matrix[2][0] = 0.000087;
  A.matrix[2][1] = 2.5668;
  A.matrix[2][2] = 1.0;

  DL_determinant(&A, &determ);
  ck_assert_double_eq(determ, -24105.996724156);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_determinant_05) {
  double determ = 0.0;
  matrix_t A = {0};

  DL_create_matrix(2, 2, &A);
  A.matrix[0][0] = -677700.0;
  A.matrix[0][1] = 654.0;
  A.matrix[1][0] = 2.0;
  A.matrix[1][1] = -0.00001;

  DL_determinant(&A, &determ);
  ck_assert_double_eq(determ, -1301.223);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_determinant_06) {
  double determ = 0.0;
  matrix_t A = {0};

  DL_create_matrix(8, 8, &A);
  DL_init_matrix(1.0, &A);

  DL_determinant(&A, &determ);
  ck_assert_double_eq(determ, 0.0);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_calc_complements_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;
  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;
  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;
  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  DL_calc_complements(&A, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2879514.0;
  X.matrix[0][1] = -1236631.0;
  X.matrix[0][2] = -1685096.0;
  X.matrix[0][3] = 880697.0;
  X.matrix[1][0] = 1162090.0;
  X.matrix[1][1] = -714015.0;
  X.matrix[1][2] = 4046255.0;
  X.matrix[1][3] = -3901600.0;
  X.matrix[2][0] = 4362897.0;
  X.matrix[2][1] = -2049432.0;
  X.matrix[2][2] = -532912.0;
  X.matrix[2][3] = -1370781.0;
  X.matrix[3][0] = 3412773.0;
  X.matrix[3][1] = -1569493.0;
  X.matrix[3][2] = 3144517.0;
  X.matrix[3][3] = 1284666.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_calc_complements_02) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  DL_calc_complements(&A, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_calc_complements_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(4, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;

  res = DL_calc_complements(&A, &Z);

  DL_remove_matrix(&A);

  ck_assert_int_eq(res, ERROR_CALC);
}
END_TEST

START_TEST(DL_calc_complements_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(2, 2, &A);
  DL_remove_matrix(&A);

  res = DL_calc_complements(&A, &Z);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_inverse_matrix_01) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  DL_inverse_matrix(&A, &Z);

  DL_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = -5.0 / 23.0;
  X.matrix[1][1] = -121.0 / 23.0;
  X.matrix[1][2] = 2.0 / 23.0;
  X.matrix[1][3] = 1.0 / 23.0;
  X.matrix[2][0] = -18.0 / 23.0;
  X.matrix[2][1] = -379.0 / 46.0;
  X.matrix[2][2] = 19.0 / 46.0;
  X.matrix[2][3] = -25.0 / 46.0;
  X.matrix[3][0] = 53.0 / 69.0;
  X.matrix[3][1] = 1061.0 / 138.0;
  X.matrix[3][2] = -47.0 / 138.0;
  X.matrix[3][3] = 19.0 / 46.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(DL_inverse_matrix_02) {
  int res;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2;

  res = DL_inverse_matrix(&A, &Z);

  ck_assert_double_eq(Z.matrix[0][0], (1.0 / A.matrix[0][0]));
  ck_assert_int_eq(res, OK);

  DL_remove_matrix(&A);
  DL_remove_matrix(&Z);
}
END_TEST

START_TEST(DL_inverse_matrix_03) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(3, 3, &A);
  DL_init_matrix(1.0, &A);

  res = DL_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, ERROR_CALC);
  DL_remove_matrix(&A);
  DL_remove_matrix(&Z);
}
END_TEST

START_TEST(DL_inverse_matrix_04) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(3, 2, &A);
  DL_init_matrix(1.0, &A);

  res = DL_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, ERROR_CALC);
  DL_remove_matrix(&A);
}
END_TEST

START_TEST(DL_inverse_matrix_05) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  DL_create_matrix(3, 3, &A);
  DL_init_matrix(1.0, &A);
  DL_remove_matrix(&A);

  res = DL_inverse_matrix(&A, &Z);

  ck_assert_int_eq(res, ERROR_INIT);
}
END_TEST

START_TEST(DL_inverse_matrix_06) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  DL_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  DL_inverse_matrix(&A, &Z);

  DL_create_matrix(3, 3, &X);

  X.matrix[0][0] = -3.0 / 5.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 1.0 / 5.0;
  X.matrix[1][0] = -4.0 / 5.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = -2.0 / 5.0;
  X.matrix[2][0] = 16.0 / 15.0;
  X.matrix[2][1] = -2.0 / 3.0;
  X.matrix[2][2] = 1.0 / 5.0;

  res = DL_eq_matrix(&X, &Z);

  DL_remove_matrix(&A);
  DL_remove_matrix(&X);
  DL_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Core");
  TCase *tc_core = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc_core);

  tcase_add_test(tc_core, DL_create_matrix_01);
  tcase_add_test(tc_core, DL_create_matrix_02);
  tcase_add_test(tc_core, DL_create_matrix_03);
  tcase_add_test(tc_core, DL_create_matrix_04);
  tcase_add_test(tc_core, DL_create_matrix_05);
  tcase_add_test(tc_core, DL_create_matrix_06);
  tcase_add_test(tc_core, DL_create_matrix_07);
  tcase_add_test(tc_core, DL_create_matrix_08);
  tcase_add_test(tc_core, DL_create_matrix_09);

  tcase_add_test(tc_core, DL_remove_matrix_01);
  tcase_add_test(tc_core, DL_remove_matrix_02);
  tcase_add_test(tc_core, DL_remove_matrix_03);
  tcase_add_test(tc_core, DL_remove_matrix_04);
  tcase_add_test(tc_core, DL_remove_matrix_05);

  tcase_add_test(tc_core, DL_eq_matrix_01);
  tcase_add_test(tc_core, DL_eq_matrix_02);
  tcase_add_test(tc_core, DL_eq_matrix_03);
  tcase_add_test(tc_core, DL_eq_matrix_04);
  tcase_add_test(tc_core, DL_eq_matrix_05);
  tcase_add_test(tc_core, DL_eq_matrix_06);

  tcase_add_test(tc_core, DL_sum_matrix_01);
  tcase_add_test(tc_core, DL_sum_matrix_02);
  tcase_add_test(tc_core, DL_sum_matrix_03);
  tcase_add_test(tc_core, DL_sum_matrix_04);
  tcase_add_test(tc_core, DL_sum_matrix_05);
  tcase_add_test(tc_core, DL_sum_matrix_06);
  tcase_add_test(tc_core, DL_sum_matrix_07);
  tcase_add_test(tc_core, DL_sum_matrix_08);
  tcase_add_test(tc_core, DL_sum_matrix_09);

  tcase_add_test(tc_core, DL_sub_matrix_01);
  tcase_add_test(tc_core, DL_sub_matrix_02);
  tcase_add_test(tc_core, DL_sub_matrix_03);
  tcase_add_test(tc_core, DL_sub_matrix_04);
  tcase_add_test(tc_core, DL_sub_matrix_05);
  tcase_add_test(tc_core, DL_sub_matrix_06);
  tcase_add_test(tc_core, DL_sub_matrix_07);
  tcase_add_test(tc_core, DL_sub_matrix_08);
  tcase_add_test(tc_core, DL_sub_matrix_09);

  tcase_add_test(tc_core, DL_mult_number_01);
  tcase_add_test(tc_core, DL_mult_number_02);
  tcase_add_test(tc_core, DL_mult_number_03);
  tcase_add_test(tc_core, DL_mult_number_04);
  tcase_add_test(tc_core, DL_mult_number_05);
  tcase_add_test(tc_core, DL_mult_number_06);

  tcase_add_test(tc_core, DL_mult_matrix_01);
  tcase_add_test(tc_core, DL_mult_matrix_02);
  tcase_add_test(tc_core, DL_mult_matrix_03);
  tcase_add_test(tc_core, DL_mult_matrix_04);
  tcase_add_test(tc_core, DL_mult_matrix_05);
  tcase_add_test(tc_core, DL_mult_matrix_06);
  tcase_add_test(tc_core, DL_mult_matrix_07);

  tcase_add_test(tc_core, DL_transpose_01);
  tcase_add_test(tc_core, DL_transpose_02);
  tcase_add_test(tc_core, DL_transpose_03);

  tcase_add_test(tc_core, DL_determinant_01);
  tcase_add_test(tc_core, DL_determinant_02);
  tcase_add_test(tc_core, DL_determinant_03);
  tcase_add_test(tc_core, DL_determinant_04);
  tcase_add_test(tc_core, DL_determinant_05);
  tcase_add_test(tc_core, DL_determinant_06);

  tcase_add_test(tc_core, DL_calc_complements_01);
  tcase_add_test(tc_core, DL_calc_complements_02);
  tcase_add_test(tc_core, DL_calc_complements_03);
  tcase_add_test(tc_core, DL_calc_complements_04);

  tcase_add_test(tc_core, DL_inverse_matrix_01);
  tcase_add_test(tc_core, DL_inverse_matrix_02);
  tcase_add_test(tc_core, DL_inverse_matrix_03);
  tcase_add_test(tc_core, DL_inverse_matrix_04);
  tcase_add_test(tc_core, DL_inverse_matrix_05);
  tcase_add_test(tc_core, DL_inverse_matrix_06);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf ? 1 : 0;
}