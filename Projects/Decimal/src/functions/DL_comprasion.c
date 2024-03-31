#include "../DL_decimal.h"

int DL_is_less(DL_decimal op_2, DL_decimal op_1) {
  int ret_bool, sign_op_1, sign_op_2, factor_op_1, factor_op_2;
  DL_get_dec_sign(op_1, &sign_op_1);
  DL_get_dec_sign(op_2, &sign_op_2);
  DL_get_dec_scale_factor(op_1, &factor_op_1);
  DL_get_dec_scale_factor(op_2, &factor_op_2);

  if (DL_is_not_equal(op_1, op_2)) {
    if (sign_op_2 == 1 && sign_op_1 == 0)
      // Если первое число отриц., а второе пол., то ложь
      ret_bool = 1;
    else if (sign_op_2 == 0 &&
             sign_op_1 == 1)  // Истина, если первое пол., а второе отриц.
      ret_bool = 0;
    else {
      cast_to_same_scale(&op_1, &op_2);
      for (int i = 95; i >= 0; i--) {
        int bit_op1 = scan_single_bit(op_1, i),
            bit_op2 = scan_single_bit(op_2, i);

        if (bit_op1 != bit_op2) {
          if (bit_op1 != 0) {
            ret_bool = (sign_op_1 == 0) ? 1 : 0;
            break;
          } else {
            ret_bool = (sign_op_1 == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  } else
    ret_bool = 0;

  return !!ret_bool;
}

int DL_is_greater(DL_decimal op_1, DL_decimal op_2) {
  int ret_bool, sign_op_1, sign_op_2, factor_op_1, factor_op_2;
  DL_get_dec_sign(op_1, &sign_op_1);
  DL_get_dec_sign(op_2, &sign_op_2);
  DL_get_dec_scale_factor(op_1, &factor_op_1);
  DL_get_dec_scale_factor(op_2, &factor_op_2);

  set_single_bit(&op_1, 98, 0);

  if (DL_is_not_equal(op_1, op_2)) {
    if (sign_op_1 == 1 && sign_op_2 == 0)
      // Если первое число отриц., а второе пол., то ложь
      ret_bool = 0;
    else if (sign_op_1 == 0 &&
             sign_op_2 == 1)  // Истина, если первое пол., а второе отриц.
      ret_bool = 1;
    else {
      cast_to_same_scale(&op_1, &op_2);
      for (int i = 95; i >= 0; i--) {
        int bit_op1 = scan_single_bit(op_1, i),
            bit_op2 = scan_single_bit(op_2, i);

        if (bit_op1 != bit_op2) {
          if (bit_op1 != 0) {
            ret_bool = (sign_op_1 == 0) ? 1 : 0;
            break;
          } else {
            ret_bool = (sign_op_1 == 0) ? 0 : 1;
            break;
          }
        }
      }
    }
  } else
    ret_bool = 0;

  return !!ret_bool;
}
/* Return values:
    0 - FALSE
    1 - TRUE
*/
