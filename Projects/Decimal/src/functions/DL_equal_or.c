#include "../DL_decimal.h"

int DL_is_less_or_equal(DL_decimal op_1, DL_decimal op_2) {
  return !DL_is_greater(op_1, op_2);
}

int DL_is_greater_or_equal(DL_decimal op_1, DL_decimal op_2) {
  return !DL_is_less(op_1, op_2);
}
/* Return values:
    0 - FALSE
    1 - TRUE
*/