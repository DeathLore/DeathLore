#include <math.h>

#include "../DL_decimal.h"

int DL_floor(DL_decimal value, DL_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }

  DL_decimal minus_null = {{0, 0, 0, 0}};
  DL_set_dec_sign(&minus_null, 1);

  int error = 0;
  int sign;
  int scale;
  DL_decimal sub_one = {{1, 0, 0, 0}};

  if (!DL_get_dec_sign(value, &sign) &&
      !DL_get_dec_scale_factor(value, &scale)) {
    DL_truncate(value, result);
    if (sign != 0 && !DL_is_equal(*result, value) &&
        !DL_is_equal(value, minus_null)) {
      DL_sub(*result, sub_one, result);
    }
  } else
    error = 1;
  return error;
}

/* Return error codes:
    0 - OK
    1 - error
*/
