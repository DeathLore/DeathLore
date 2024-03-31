#ifndef DL_DECIMAL
#define DL_DECIMAL

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_255 255

#define DEC_MAX 4294967296
#define DL_MAX_UINT 4294967295

/* unsigned int bits[4] = {0, 0, 0, 0}
   bit[0] - num section; bit[1] - num section; bit[2] - num section;

   bit[3] - dec info; 0-15 bits are zero; 16-23 bits are scale factor;
   24-30 bits are zero; 31 is sign bit.
   [s0000000ffffffff0000000000000000]: s - sign; f - scale factor;
*/
typedef struct DL_decimal {
  unsigned int bits[4];
} DL_decimal;

// Arithmetics!

// Decimal addition operator (+)
int DL_add(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);
int DL_add2(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);
// Decimal subtraction operator (-)
int DL_sub(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);
// Decimal multiplication operator (*)
int DL_mul(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);
// Decimal division operator (/)
int DL_div(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);
/* return error codes:
    0 - OK
    1 - the number is too large or equal to infinity
    2 - the number is too small or equal to negative infinity
    3 - division by 0
*/

// Comparison!

// Decimal less_than operator (<)
int DL_is_less(DL_decimal op_1, DL_decimal op_2);
// Decimal less_than_or_equal_to operator (<=)
int DL_is_less_or_equal(DL_decimal op_1, DL_decimal op_2);
// Decimal greater_than operator (>)
int DL_is_greater(DL_decimal op_1, DL_decimal op_2);
// Decimal greater_than_or_equal_to operator (>=)
int DL_is_greater_or_equal(DL_decimal op_1, DL_decimal op_2);
// Decimal equal_to operator (==)
int DL_is_equal(DL_decimal op_1, DL_decimal op_2);
// Decimal not_equal_to operator (!=)
int DL_is_not_equal(DL_decimal op_1, DL_decimal op_2);
/* Return values:
    0 - FALSE
    1 - TRUE
*/

// Convertors and parsers!

// Decimal from int (int -> dec)
int DL_from_int_to_decimal(int src, DL_decimal *dst);
// Decimal from float (float -> dec)
int DL_from_float_to_decimal(float src, DL_decimal *dst);
// Decimal to int (dec -> int)
int DL_from_decimal_to_int(DL_decimal src, int *dst);
// Decimal to float (dec -> float)
int DL_from_decimal_to_float(DL_decimal src, float *dst);
/* Return error codes:
    0 - OK
    1 - convertation error
*/

// Another DL functions!

// Round DOWN value (3,16 -> 3,1; 3,14 ->3,1)
int DL_floor(DL_decimal value, DL_decimal *result);
// Round UP value (3,16 -> 3,2; 3,14 -> 3,1)
int DL_round(DL_decimal value, DL_decimal *result);
// Cut off fraction (3,14 -> 3)
int DL_truncate(DL_decimal value, DL_decimal *result);
// Multiply by "-1" (3,14 -> -3,14 || -3,14 -> 3,14)
int DL_negate(DL_decimal value, DL_decimal *result);
/* Return error codes:
    0 - OK
    1 - calculation error
*/

// Additional functions!

/* Sets decimal variable
   sign - decimal sign: 0 - positive, 1 - negative;
   scale_factor - decimal scale factor with possible values between 28 and 0
   (including);
   bit2 - sets dec.bits[2];
   bit1 - sets dec.bits[1];
   bit0 - sets dec.bits[0];

   If sign or scale are incorrect - returns zero decimal {0,0,0,0,0}.
*/
DL_decimal DL_create(int sign, int scale_factor, unsigned int bit2,
                     unsigned int bit1, unsigned int bit0);
// Get sign value of decimal (0 - positive; 1 - negative)
int DL_get_dec_sign(DL_decimal value, int *result);
// Get scale factor of decimal
int DL_get_dec_scale_factor(DL_decimal value, int *result);
// Set sign value of decimal (0 - positive; 1 - negative)
int DL_set_dec_sign(DL_decimal *result, int value);
// Set scale factor of decimal
int DL_set_dec_scale_factor(DL_decimal *result, int value);
// Greater if scale factors are equal
int DL_is_greater(DL_decimal op_1, DL_decimal op_2);

DL_decimal *set_single_bit(DL_decimal *const mutable_val, int const bit_number,
                           int const new_bit_val);
void cast_to_same_scale(DL_decimal *decimal1, DL_decimal *decimal2);
int scan_single_bit(DL_decimal const scaned_val, int const bit_position_number);

int DL_mult_ten(DL_decimal *value);
void DL_bit_sub(DL_decimal value_1, DL_decimal value_2, DL_decimal *result);

void dec_left_shift(DL_decimal *result, int shift);

/* Return error codes:
    0 - OK
    1 - error
*/

#endif