#include "../DL_decimal.h"

int DL_get_dec_sign(DL_decimal value,
                    int *result) {  // функция для получения степни числа
  int error = 1;
  unsigned int res = value.bits[3];
  res = res >> 30;  // [11111111111111111111111111111100] ||
                    // [00000000000000000000000000000000]
  res = res << 30;  // [10000000000000000000000000000000] = 2147483648 ||
                    // [00000000000000000000000000000000]
  if (res == 0 || res == 2147483648) {
    error = 0;
    *result = (res == 0) ? 0 : 1;
  }

  return error;
}

int DL_set_dec_sign(DL_decimal *result,
                    int value) {  // функция для задавания степени числа
  int begin_sign = 0, error = 1, flag_coppy = 0;
  DL_decimal buf = {0};
  if (value == 1 || value == 0) {
    buf.bits[3] = result->bits[3];
    DL_get_dec_sign(buf, &begin_sign);
    if (value != begin_sign) {
      buf.bits[3] += 2147483648;  // Если текущее значение не равно
                                  // необходимому, то изменяем его на нужное
      flag_coppy = 1;
    }

    DL_get_dec_sign(buf, &begin_sign);
    if (value == begin_sign) {
      error = 0;
      if (flag_coppy) result->bits[3] = buf.bits[3];
      // Если всё правильно скопировано и копировать надо - записываем результат
    }
  }

  return error;
}

/* Return error codes:
    0 - OK
    1 - error
*/