#include "../DL_decimal.h"

int DL_is_equal(DL_decimal op_1, DL_decimal op_2) {
  int ret_bool;
  cast_to_same_scale(&op_1, &op_2);
  int sign1, sign2, factor_op_1, factor_op_2;
  DL_get_dec_sign(op_1, &sign1);
  DL_get_dec_sign(op_2, &sign2);
  DL_get_dec_scale_factor(op_1, &factor_op_1);
  DL_get_dec_scale_factor(op_2, &factor_op_2);

  // if (scan_single_bit(op_1, 97)){
  //   printf("\n a: %d, %d\nb: %d, %d\n", sign1, factor_op_1, sign2,
  //   factor_op_2);
  // }

  if (op_1.bits[0] == 0 && op_1.bits[1] == 0 && op_1.bits[2] == 0 &&
      op_1.bits[0] == op_2.bits[0] && op_1.bits[1] == op_2.bits[1] &&
      op_1.bits[2] == op_2.bits[2])
    ret_bool = 1;
  else if (sign1 == sign2 && op_1.bits[0] == op_2.bits[0] &&
           op_1.bits[1] == op_2.bits[1] && op_1.bits[2] == op_2.bits[2] &&
           op_1.bits[3] == op_2.bits[3])
    ret_bool = 1;
  else
    ret_bool = 0;

  return ret_bool;
}

int DL_is_not_equal(DL_decimal op_1, DL_decimal op_2) {
  int ret_bool;

  cast_to_same_scale(&op_1, &op_2);
  int sign1, sign2;
  DL_get_dec_sign(op_1, &sign1);
  DL_get_dec_sign(op_2, &sign2);
  if (op_1.bits[0] == 0 && op_1.bits[1] == 0 && op_1.bits[2] == 0 &&
      op_1.bits[0] == op_2.bits[0] && op_1.bits[1] == op_2.bits[1] &&
      op_1.bits[2] == op_2.bits[2])
    ret_bool = 0;
  else if (sign1 != sign2 || op_1.bits[0] != op_2.bits[0] ||
           op_1.bits[1] != op_2.bits[1] || op_1.bits[2] != op_2.bits[2] ||
           op_1.bits[3] != op_2.bits[3])
    ret_bool = 1;
  else
    ret_bool = 0;  // В целях оптимизации, функция была сделана с нуля, что-бы
                   // не вызвала другую.

  return ret_bool;
}
/* Return values:
    0 - FALSE
    1 - TRUE
*/