#include <math.h>

#include "../DL_decimal.h"

int return_last_digit_and_truncate_buf_by_it(DL_decimal *buf) {
  unsigned long long u_num;
  int tmp_int = 0;
  u_num = buf->bits[2];
  int j = 2;
  for (; j >= 0; j--) {
    if (j == 0) {
      tmp_int = u_num % 10;
      buf->bits[j] = u_num / 10;
    } else {
      tmp_int = u_num % 10;
      buf->bits[j] = u_num / 10;
      u_num = tmp_int * (DL_MAX_UINT + 1) + buf->bits[j - 1];
    }
  }
  return tmp_int;
}

void DL_truncate_buf(DL_decimal *buf, int exp) {
  unsigned long long u_num;  // 18,446,744,073,709,551,615
  int tmp_int = 0;
  for (int i = 0; i < exp; i++) {
    u_num = buf->bits[2];
    int j = 2;
    for (; j >= 0; j--) {
      if (j == 0) {
        buf->bits[j] = u_num / 10;
      } else {
        tmp_int = u_num % 10;  // запомнили первый разряд который мы отнимаем
        buf->bits[j] = u_num / 10;  // получили в последнем инте валуе получили
                                    // последний инт резалта
        u_num = tmp_int * (4294967296) + buf->bits[j - 1];
      }
    }
  }
  buf->bits[3] = 0;
}

int DL_round(DL_decimal value, DL_decimal *result) {
  int error = 0;
  int sign_op = 0;

  int exp = 0;
  int power = 1;
  for (int i = 112; i < 117; i++, power = power * 2)
    if (scan_single_bit(value, i)) exp += power;

  int last_digit = 0;
  DL_decimal *res = result;

  DL_get_dec_sign(value, &sign_op);

  if (exp != 0) {
    DL_decimal buf = {0};
    buf = value;
    DL_truncate_buf(&buf, exp - 1);
    last_digit = return_last_digit_and_truncate_buf_by_it(&buf);
    *res = buf;
    if (last_digit >= 5) {
      DL_decimal one = {{1, 0, 0, 0}};
      if (last_digit == 5) {
        if (scan_single_bit(*res, 0)) {
          DL_add(*res, one, res);
        }
      } else if (last_digit > 5)
        DL_add(*res, one, res);
    }
    *result = *res;
    if (sign_op) {
      DL_set_dec_sign(result, 1);
    }
  } else {
    *result = value;
  }

  return error;
}

/* Return error codes:
    0 - OK
    1 - error
*/
