#include "../DL_decimal.h"

int DL_get_exp(DL_decimal *src) { return (src->bits[3] & 0xFF0000) >> 16; }

int DL_from_decimal_to_float(DL_decimal src, float *dst) {
  *dst = 0;
  for (int i = 0; i < 96; i++) {
    if (scan_single_bit(src, i)) {
      *dst += scan_single_bit(src, i) * pow(2, i);
    }
  }
  *dst /= pow(10, DL_get_exp(&src));
  int sign;
  DL_get_dec_sign(src, &sign);
  if (sign) {
    *dst = -*dst;
  }
  return 0;
}
