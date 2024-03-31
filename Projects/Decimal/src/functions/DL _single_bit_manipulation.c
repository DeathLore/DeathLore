#include "../DL_decimal.h"

// Sets appropriate bit in appr. position in some value.
// Sets just bit in the whole value (1 or 0).
//
// bits[0]: 0-31; bits[1]: 32-63; bits[2]: 64-95; bits[3]: 96-128.
DL_decimal* set_single_bit(DL_decimal* const mutable_val, int const bit_number,
                           int const new_bit_val) {
  if (bit_number / 32 < 4 && new_bit_val)
    mutable_val->bits[bit_number / 32] |= (1 << (bit_number % 32));
  else if (bit_number / 32 < 4 && !new_bit_val)
    mutable_val->bits[bit_number / 32] &= ~(1 << (bit_number % 32));
  return mutable_val;
}

// Scans bit position in some value and returns scaned bit (1 or 0).
//
// bits[0]: 0-31; bits[1]: 32-63; bits[2]: 64-95; bits[3]: 96-128.
int scan_single_bit(DL_decimal const scaned_val,
                    int const bit_position_number) {
  int ret_bit, bit_mask = 1 << (bit_position_number % 32);

  ret_bit = (scaned_val.bits[bit_position_number / 32] & bit_mask) != 0 ? 1 : 0;

  return ret_bit;
}

// Для отладки
// void printBits(unsigned int value) {
//   unsigned int mask = 1 << ((sizeof(unsigned int) << 3) - 1);
//   while (mask) {
//     printf("%d", (value & mask ? 1 : 0));
//     mask >>= 1;
//   }
// }