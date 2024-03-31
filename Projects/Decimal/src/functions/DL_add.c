#include <math.h>
#include <stdio.h>

#include "../DL_decimal.h"

int sum_of_mantis(DL_decimal a, DL_decimal b, DL_decimal *result) {
  int error = 0;
  unsigned long int ost = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long int temp = a.bits[i] + b.bits[i];
    temp += ost;
    result->bits[i] = (int)temp;
    ost = temp >> 32;
    error = temp;
  }
  return error != 0 ? 1 : 0;
}

int DL_add(DL_decimal value_1, DL_decimal value_2, DL_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = 0;

  int scale_1 = 0, scale_2 = 0;
  int sign_1 = 0, sign_2 = 0;
  error = error || DL_get_dec_scale_factor(value_1, &scale_1);
  error = error || DL_get_dec_scale_factor(value_2, &scale_2);

  error = error || DL_get_dec_sign(value_1, &sign_1);
  error = error || DL_get_dec_sign(value_2, &sign_2);
  if (!error) {
    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0 &&
        sign_1 != 0)
      DL_set_dec_sign(&value_1, 0);

    int difference = scale_1 - scale_2;
    // если первое число +, а второе -, то вычитаем value_1 - value_2
    if (sign_1 == 0 && sign_2 == 1) {
      DL_set_dec_sign(&value_2, 0);
      error = error || DL_sub(value_1, value_2, result);

      // если первое число -, а второе +, то вычитаем value_2 - value_1
    } else if (sign_1 == 1 && sign_2 == 0) {
      DL_set_dec_sign(&value_1, 0);
      error = error || DL_sub(value_2, value_1, result);
    } else {  // если знаки равны, то суммируем
      if (difference > 0) {
        while (scale_1 > scale_2) {
          DL_mult_ten(&value_2);
          scale_2++;
        }
        error = error || sum_of_mantis(value_1, value_2, result);
      } else if (difference < 0) {
        while (scale_1 < scale_2) {
          DL_mult_ten(&value_1);
          scale_1++;
        }
        error = error || sum_of_mantis(value_1, value_2, result);
      } else {
        error = error || sum_of_mantis(value_1, value_2, result);
      }
      DL_set_dec_sign(result, sign_1);  // в конце добавляем знак
      DL_set_dec_scale_factor(result, scale_1);
    }
  }

  if (sign_1 && error) error = 2;

  return error;
}

/* return error codes:
    0 - OK
    1 - the number is too large or equal to infinity
    2 - the number is too small or equal to negative infinity
    3 - division by 0
*/