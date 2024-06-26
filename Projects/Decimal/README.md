## О проекте:
В этом проекте создаётся свой тип данных с плавающей точкой.

```C
typedef struct DL_decimal {
  unsigned int bits[4];
} DL_decimal;
```
`bits[0]` - `bits[3]` отводятся для хранения самих данных о числе (мантисса). В `bits[4]` хранится знак числа и место, где стоит запятая (порядок).

Функции отвечающие за взаимодействие с этим типом можно разделить на 5 типов:
1. Арифметические
2. Логические
3. Приведения
4. Округление
5. Вспомогательные

К вспомогательным относятся файлы: `DL_dec_sign.c`, `DL_dec_scale_factor.c`, `DL_create_dec.c`, `DL_cast_decimal_to_same_scale.c`, `DL_single_bit_manipulation.c`.

Файлы округлений: `DL_truncate.c`, `DL_round.c`, `DL_floor.c`.

Приведение: `DL_from_int_to_decimal.c`, `DL_from_float_to_decimal.c`, `DL_from_decimal_to_int.c`, `DL_from_decimal_to_float.c`.

Логические: `DL_equality.c`, `DL_equal_or.c`, `DL_comparison.c`.

Арифметические: `DL_sub.c`, `DL_negate.c`, `DL_add`. К сожалению, операции умножения и деления не реализовал; можно было сделать банальным зацикливанием сложения и вычитания, но это крайне не эффективный способ, а времени зацикливаться на этом проекте - не было.

---
## Как использовать проект.
В проекте есть Makefile.

Стадия `DL_decimal.a` - создаёт статическую библиотеку. (вызывается как `make DL_decimal.a` в директории с файлом).

`test` - создаст библиотеку и запустит её тестирование.

`gcov_report` - запуск проверки покрытия и формирование html отчёта. Отчёт будет храниться в директории `report/functions/`, под именем `index.html` (`report/functions/index.html`).

`clean` - чистит всё от результатов работы других стадий.