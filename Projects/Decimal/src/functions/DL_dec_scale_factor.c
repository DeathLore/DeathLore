#include "../DL_decimal.h"

int DL_get_dec_scale_factor(
    DL_decimal value, int *result) {  // функция для получение степени числа
  int error = 1,
      res = 0b11111111 << 16;  // Подготовили маску, для получения степени.
  unsigned int scale = value.bits[3];
  res = (scale & res) >>
        16;  // Значение bit[3] сравниваем с маской, чтобы получить
             // только биты из степени, и сдвигаем их в начало.
  if (res <= 28 && res >= 0) {
    error = 0;  // если коэфицент больше или меньше чем должен быть - ошибка.
    *result = res;
  }

  return error;
}

int DL_set_dec_scale_factor(DL_decimal *result,
                            int value) {  // функция для задавания степени числа
  int error = 1, check;
  DL_decimal buf = {0};
  if (value <= 28 && value >= 0) {
    buf.bits[3] = result->bits[3];

    buf.bits[3] &= 1 << 31;  // Оставляем только бит знака
    buf.bits[3] |= value << 16;  // Вписываем коэффицент

    DL_get_dec_scale_factor(buf, &check);
    if (check == value) {
      error = 0;
      result->bits[3] = buf.bits[3];
      // Если скопировалось правильно - записываем результат
    }
  }

  return error;
}

/* Return error codes:
    0 - OK
    1 - error
*/