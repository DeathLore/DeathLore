#include "../DL_decimal.h"

int getFloatExp(float *value) {
  return ((*((int *)value) & ~(1u << 31)) >> 23) - 127;
}

typedef union {
  int ui;
  float fl;
} fbits;

int DL_from_float_to_decimal(float src, DL_decimal *dst) {
  int res = 1, exp = getFloatExp(&src);
  if (dst && src != 0 && !isinf(src)) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    int sign = 0;
    if (src < 0) {
      src *= -1;
      sign = 1;
    }
    double tmp = (double)src;
    int scale = 0;
    while (scale < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      scale++;
    }
    if (scale <= 28 && (exp > -94 && exp < 96)) {
      fbits mant;
      tmp = (float)tmp;
      for (; fmod(tmp, 10) == 0 && scale > 0; scale--, tmp /= 10) {
      }
      mant.fl = tmp;
      exp = getFloatExp(&mant.fl);
      set_single_bit(dst, exp, 1);
      for (int i = exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mant.ui & (1 << j)) != 0) {
          set_single_bit(dst, i, 1);
        }
      }
      DL_set_dec_sign(dst, sign);
      DL_set_dec_scale_factor(dst, scale);
      res = 0;
    }
  }
  return res;
}
