#include "../DL_decimal.h"

int DL_from_decimal_to_int(DL_decimal src, int *dst) {
  int error = 0;
  DL_decimal src_trunc;
  DL_truncate(src, &src_trunc);
  if ((src_trunc.bits[2] == 0) && (src_trunc.bits[1] == 0)) {
    *dst = src_trunc.bits[0];

    int sign = 0;
    DL_get_dec_sign(src_trunc, &sign);
    if (sign) (*dst) *= -1;

  } else {
    error = 1;
  }

  return error;
}
