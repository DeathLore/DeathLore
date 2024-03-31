#include "../DL_decimal.h"

DL_decimal DL_create(
    int sign, int scale_factor,
    unsigned int bit2,  // создание и заполнение перменной типа decimal
    unsigned int bit1, unsigned int bit0) {
  DL_decimal ret_dec = {0};

  if ((sign == 1 || sign == 0) && (scale_factor <= 28 && scale_factor >= 0)) {
    DL_set_dec_sign(&ret_dec, sign);
    DL_set_dec_scale_factor(&ret_dec, scale_factor);
    ret_dec.bits[2] = bit2;
    ret_dec.bits[1] = bit1;
    ret_dec.bits[0] = bit0;
  }

  return ret_dec;
}