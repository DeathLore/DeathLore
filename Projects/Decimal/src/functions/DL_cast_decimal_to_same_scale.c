#include "../DL_decimal.h"

void dec_left_shift(DL_decimal* result, int shift) {
  for (int y = 0; y < shift; y += 1) {
    int bit_to_transfer_1 = scan_single_bit(*result, 31);
    int bit_to_transfer_2 = scan_single_bit(*result, 63);
    for (int x = 0; x < 3; x += 1) result->bits[x] <<= 1;
    if (bit_to_transfer_1) set_single_bit(result, 32, 1);
    if (bit_to_transfer_2) set_single_bit(result, 64, 1);
  }
}
void divide_by_10(DL_decimal* result, int shift);

int sub_multiply_by_10(DL_decimal* const result,
                       DL_decimal const* const buf_shift_1,
                       DL_decimal const* const buf_shift_3) {
  unsigned long int buf = 0;

  for (int i = 0; i < 3; i++) {
    buf = buf + buf_shift_1->bits[i] + buf_shift_3->bits[i];
    result->bits[i] = buf % DEC_MAX;
    buf /= DEC_MAX;
  }
  // Если "buf" равен 1 - уменьшить степень "result" на 1, и значение на 10!
  // Потом вставить последний бит.
  return buf;
}

void dec_multiplu_by_10(DL_decimal* result, int shift) {
  int scale_res;
  int overflow = 0;
  for (; shift && !overflow; shift -= 1) {
    DL_get_dec_scale_factor(*result, &scale_res);
    if (scale_res + 1 < 29) {
      int last_bit = 95;
      for (; (last_bit >= 0) && (!scan_single_bit(*result, last_bit));)
        last_bit -= 1;
      DL_decimal buf_shift_1 = *result, buf_shift_3 = *result;
      if (last_bit + 3 < 96) {
        dec_left_shift(&buf_shift_1, 1);
        dec_left_shift(&buf_shift_3, 3);
        overflow =
            sub_multiply_by_10(result, &buf_shift_1,
                               &buf_shift_3);  // Результат умножения на 1010.
        // Если "overflow" равен 1 - уменьшить степень на 1, и значением
        // децемала на 10! Потом вставить последний бит.
        scale_res += 1;
        DL_set_dec_scale_factor(result, scale_res);
      }
    } else
      overflow = 1;
  }
  if (overflow) {
    divide_by_10(result, 1);
    scale_res -= 1;
    DL_set_dec_scale_factor(result, scale_res);
    set_single_bit(result, 95, 1);
  }
}

void divide_by_10(DL_decimal* result, int shift) {
  for (; shift; shift -= 1) {
    for (int y = 0; y < shift; y += 1) {
      unsigned long long overflow = result->bits[2];
      for (int x = 2; x >= 0; x -= 1) {
        result->bits[x] = overflow / 10;
        overflow =
            (overflow % 10) * (4294967295 + 1) + result->bits[x ? x - 1 : x];
      }
    }
  }
}

void cast_to_same_scale(DL_decimal* decimal1, DL_decimal* decimal2) {
  int scale_dec1, scale_dec2;
  DL_get_dec_scale_factor(*decimal1, &scale_dec1);
  DL_get_dec_scale_factor(*decimal2, &scale_dec2);

  if (scale_dec1 != scale_dec2) {
    if (scale_dec1 < scale_dec2)
      cast_to_same_scale(decimal2, decimal1);
    else {
      dec_multiplu_by_10(decimal2, scale_dec1 - scale_dec2);
      DL_get_dec_scale_factor(*decimal2, &scale_dec2);

      divide_by_10(decimal1, scale_dec1 - scale_dec2);
      DL_set_dec_scale_factor(decimal1, scale_dec2);
    }
  }
}
