#include "../DL_decimal.h"

int DL_mult_ten(DL_decimal *value) {
  int error = 0;
  int moved_bit = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long int temp = value->bits[i];
    temp *= 10;
    temp += moved_bit;
    value->bits[i] = temp & 0xffffffff;
    moved_bit = temp >> 32;
  }
  if (moved_bit != 0) {
    error = 1;
  }
  return error;
}

void DL_bit_sub(DL_decimal value_1, DL_decimal value_2, DL_decimal *result) {
  int check = 0;
  int buff = 0;
  for (int i = 0; i < 96; i++) {
    check = scan_single_bit(value_1, i) - scan_single_bit(value_2, i);
    if (check == 0) {
      if (buff == 1) {
        result = set_single_bit(result, i, 1);
      } else {
        result = set_single_bit(result, i, 0);
      }
    } else if (check == 1) {
      if (buff == 1) {
        result = set_single_bit(result, i, 0);
        buff = 0;
      } else {
        result = set_single_bit(result, i, 1);
      }
    } else if (check == -1) {
      if (buff == 1) {
        result = set_single_bit(result, i, 0);
      } else {
        result = set_single_bit(result, i, 1);
        buff = 1;
      }
    }
  }
}

int DL_sub(DL_decimal value_1, DL_decimal value_2, DL_decimal *result) {
  memset(&(result->bits), 0, sizeof(result->bits));
  int error = 0;
  int result_sign = 0;

  int scale_1 = 0, scale_2 = 0;
  int sign_1 = 0, sign_2 = 0;
  error = error || DL_get_dec_scale_factor(value_1, &scale_1);
  error = error || DL_get_dec_scale_factor(value_2, &scale_2);

  error = error || DL_get_dec_sign(value_1, &sign_1);
  error = error || DL_get_dec_sign(value_2, &sign_2);

  if (!error) {
    int switch_flag = 1;
    if (value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) {
      DL_set_dec_sign(&value_2, !sign_2);
      result->bits[0] = value_2.bits[0];
      result->bits[1] = value_2.bits[1];
      result->bits[2] = value_2.bits[2];
      result->bits[3] = value_2.bits[3];
      switch_flag = 0;
    }
    if (switch_flag && value_2.bits[0] == 0 && value_2.bits[1] == 0 &&
        value_2.bits[2] == 0) {
      DL_set_dec_sign(&value_1, !sign_1);
      result->bits[0] = value_1.bits[0];
      result->bits[1] = value_1.bits[1];
      result->bits[2] = value_1.bits[2];
      result->bits[3] = value_1.bits[3];
    }
    int difference = scale_1 - scale_2;

    if (sign_1 == 0 && sign_2 == 1) {  // 1 -> +; 2 -> -
      DL_set_dec_sign(&value_2, 0);
      error = error || DL_add(value_1, value_2, result);
    } else if (sign_1 == 1 && sign_2 == 0) {  // 1 -> -; 2 -> +
      DL_set_dec_sign(&value_2, 1);
      error = error || DL_add(value_1, value_2, result);
    } else if (sign_1 == 1 && sign_2 == 1) {  // 1 -> -; 2 -> -
      DL_set_dec_sign(&value_1, 0);
      DL_set_dec_sign(&value_2, 0);
      error = error || DL_sub(value_2, value_1, result);
    } else {
      if (DL_is_greater(value_2, value_1)) {
        DL_set_dec_sign(result, 1);
        result_sign = 1;
      }

      if (difference > 0) {
        while (scale_1 > scale_2) {
          DL_mult_ten(&value_2);
          scale_2++;
        }
      } else if (difference < 0) {
        while (scale_1 < scale_2) {
          DL_mult_ten(&value_1);
          scale_1++;
        }
      }
      if (result_sign == 1) {
        DL_bit_sub(value_2, value_1, result);
      } else {
        DL_bit_sub(value_1, value_2, result);
      }
      DL_set_dec_scale_factor(result, scale_1);
    }
  }
  return error;
}

/* return error codes:
    0 - OK
    1 - the number is too large or equal to infinity
    2 - the number is too small or equal to negative infinity
    3 - division by 0
*/