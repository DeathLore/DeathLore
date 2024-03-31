#include "../DL_decimal.h"

int DL_div_ten(DL_decimal *value) {
  int error = 0;
  unsigned long int residue = 0;  // остаток от деления
  unsigned long int x = 0;
  for (int i = 2; i >= 0; --i) {
    x = value->bits[i];
    x += (residue << 32);
    residue = x % 10;
    x /= 10;
    value->bits[i] = x;
  }
  return error;
}

int DL_truncate(DL_decimal value, DL_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }

  int error = 0;
  int sign;
  int scale;
  if (!DL_get_dec_sign(value, &sign) &&
      !DL_get_dec_scale_factor(value, &scale)) {
    *result = value;
    while (scale) {
      DL_div_ten(result);
      scale--;
    }
    DL_set_dec_scale_factor(result, 0);

  } else
    error = 1;
  return error;
}

/* Return error codes:
    0 - OK
    1 - error
*/
