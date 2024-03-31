#include "../DL_decimal.h"

int DL_negate(DL_decimal value, DL_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
  int sign;
  int error = DL_get_dec_sign(value, &sign);
  if (!error) error = DL_set_dec_sign(result, !sign);

  return error;
}
