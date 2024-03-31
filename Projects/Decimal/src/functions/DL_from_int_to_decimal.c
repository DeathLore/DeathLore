#include "../DL_decimal.h"

int DL_from_int_to_decimal(int src, DL_decimal *dst) {
  int error = 0;
  int sign = 0;

  for (int i = 0; i < 128; ++i) {
    set_single_bit(dst, i, 0);
  }

  if (src != 0) {
    if (src < 0) {
      sign = 1;
      src = -src;
    }
    dst->bits[0] = src;
    DL_set_dec_scale_factor(dst, 0);
    DL_set_dec_sign(dst, sign);
  }
  return error;
}
