#include "DL_test.h"

// is_less
START_TEST(DL_less_test_1) {  // 2  3
  DL_decimal value_1 = {{2, 0, 0, 0}};
  DL_decimal value_2 = {{3, 0, 0, 0}};
  ck_assert_int_eq(DL_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(positive_zero_and_positive_zero) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(positive_zero_and_negative_zero) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&first, 1);

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_less_then_second) {
  DL_decimal first = {.bits = {35, 34, 0, 0}};
  DL_decimal second = {.bits = {0, 35, 0, 0}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(second_less_then_first) {
  DL_decimal first = {.bits = {0, 0, 1, 0}};
  DL_decimal second = {.bits = {1231, 748, 0, 0}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_less_negative_sign) {
  DL_decimal first = {.bits = {0, 0, 1, 0x80000000}};
  DL_decimal second = {.bits = {0, 0, 1, 0}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(equal) {
  DL_decimal first = {.bits = {60, 56, 134, 0x80000000}};
  DL_decimal second = {.bits = {60, 56, 134, 0x80000000}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(same_value_different_scale_first_less) {
  DL_decimal first = {.bits = {60, 56, 134, 0x80000}};
  DL_decimal second = {.bits = {60, 56, 134, 0x8000}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_all_first_less) {
  DL_decimal first = {.bits = {123, 9, 132, 0x80000}};
  DL_decimal second = {.bits = {12, 52, 154, 0x8000000}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_all_second_less) {
  DL_decimal first = {.bits = {12, 52, 154, 0x8000000}};
  DL_decimal second = {.bits = {123, 9, 132, 0x80000}};

  int res = DL_is_less(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

// is_less_or_equal
START_TEST(positive_zero_and_positive_zero_le) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(positive_zero_and_negative_zero_le) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&first, 1);

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_less_then_second_le) {
  DL_decimal first = {.bits = {35, 34, 0, 0}};
  DL_decimal second = {.bits = {0, 35, 0, 0}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(second_less_then_first_le) {
  DL_decimal first = {.bits = {0, 0, 1, 0}};
  DL_decimal second = {.bits = {1231, 748, 0, 0}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_less_negative_sign_le) {
  DL_decimal first = {.bits = {0, 0, 1, 0x80000000}};
  DL_decimal second = {.bits = {0, 0, 1, 0}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(equal_le) {
  DL_decimal first = {.bits = {60, 56, 134, 0x80000000}};
  DL_decimal second = {.bits = {60, 56, 134, 0x80000000}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_value_different_scale_first_less_le) {
  DL_decimal first = {.bits = {60, 56, 134, 0x80000}};
  DL_decimal second = {.bits = {60, 56, 134, 0x1000}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_all_first_less_le) {
  DL_decimal first = {.bits = {123, 9, 132, 0x80000}};
  DL_decimal second = {.bits = {12, 52, 154, 0x8000000}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_all_second_less_le) {
  DL_decimal first = {.bits = {12, 52, 154, 0x8000000}};
  DL_decimal second = {.bits = {123, 9, 132, 0x80000}};

  int res = DL_is_less_or_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

// is_greater

START_TEST(positive_zero_and_negative_zero_gr) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&second, 1);
  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_greater_then_second_gr) {
  DL_decimal first = {{0, 0, 1, 0}};
  DL_decimal second = {{98761, 12312, 0, 0}};

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_less_then_second_gr) {
  DL_decimal first = {{98761, 12312, 0, 0}};
  DL_decimal second = {{0, 0, 1, 0}};

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(value_equal_first_positive_second_negative_gr) {
  DL_decimal first = {.bits = {98761, 123, 1, 0}};
  DL_decimal second = {.bits = {98761, 123, 1, 0x80000000}};

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_value_less_first_scale_less_first_greater_gr) {
  DL_decimal first = {{35, 1123, 0, 0x1000}};
  DL_decimal second = {{98761, 123, 1, 0x80000}};

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_value_less_first_negative_gr) {
  DL_decimal first = {{35, 1123, 0, 0x1000}};
  DL_decimal second = {{98761, 123, 1, 0x80000}};
  DL_set_dec_sign(&first, 1);

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_value_less_first_negative_second_negative_gr) {
  DL_decimal first = {{35, 1123, 0, 0x80000}};
  DL_decimal second = {{98761, 123, 1, 0x1000}};

  DL_set_dec_sign(&first, 1);
  DL_set_dec_sign(&second, 1);

  int res = DL_is_greater(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

// is_greater_or_equal

START_TEST(DL_is_greater_or_equal_0) {
  DL_decimal src1 = DL_create(0, 9, 0, 0b10, 0);
  // src1 = 5.492654545456454545645464;

  // src1.bits[0] = 0b00000111100110110001111110011000;
  // src1.bits[1] = 0b01100110010010001001000110100011;
  // src1.bits[2] = 0b00000000000001001000101100011101;
  // src1.bits[3] = 0b00000000000110000000000000000000;
  DL_decimal half_of_one = {{86, 0, 0, 0}};
  DL_set_dec_scale_factor(&half_of_one, 1);
  set_single_bit(&src1, 98, 1);

  // int sign1, sign2, factor_op_1, factor_op_2;
  // DL_get_dec_sign(src1, &sign1);
  // DL_get_dec_sign(half_of_one, &sign2);
  // DL_get_dec_scale_factor(src1, &factor_op_1);
  // DL_get_dec_scale_factor(half_of_one, &factor_op_2);
  // printf("\n a: %d, %d; 0: ", sign1, factor_op_1);
  // printBits(src1.bits[0]);
  // printf(" 1: ");
  // printBits(src1.bits[1]);
  // printf(" 2: ");
  // printBits(src1.bits[2]);
  // printf("\n");
  // printf(" b: %d, %d; 0: ", sign2, factor_op_2);
  // printBits(half_of_one.bits[0]);
  // printf(" 1: ");
  // printBits(half_of_one.bits[1]);
  // printf(" 2: ");
  // printBits(half_of_one.bits[2]);
  // printf("\n %u\n", 0 - 1);
  // int res = DL_is_equal(src1, half_of_one);

  int res = DL_is_greater_or_equal(src1, half_of_one);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(positive_zero_and_negative_zero_ge) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;

  DL_set_dec_sign(&second, 1);

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_greater_then_second_ge) {
  DL_decimal first = {{0, 0, 1, 0}};
  DL_decimal second = {{98761, 12312, 0, 0}};

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_less_then_second_ge) {
  DL_decimal first = {{98761, 12312, 0, 0}};
  DL_decimal second = {{0, 0, 1, 0}};

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(value_equal_first_positive_second_negative_ge) {
  DL_decimal first = {{98761, 123, 1, 0}};
  DL_decimal second = {{98761, 123, 1, 0x80000000}};

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_value_less_first_scale_less_first_greater_ge) {
  DL_decimal first = {{35, 1123, 0, 0x1000}};
  DL_decimal second = {{98761, 123, 1, 0x80000}};

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(first_value_less_first_negative_ge) {
  DL_decimal first = {{35, 1123, 0, 0x1000}};
  DL_decimal second = {{98761, 123, 1, 0x80000}};
  DL_set_dec_sign(&first, 1);

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(first_value_less_first_negative_second_negative_ge) {
  DL_decimal first = {{35, 1123, 0, 0x80000}};
  DL_decimal second = {{98761, 123, 1, 0x1000}};

  DL_set_dec_sign(&first, 1);
  DL_set_dec_sign(&second, 1);

  int res = DL_is_greater_or_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

// is_equal

START_TEST(positive_zero_equal_other_positive_zero_e) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(negative_zero_equal_other_negative_zero_e) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&first, 1);
  DL_set_dec_sign(&second, 1);

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(positive_zero_equal_negative_zero_e) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&second, 1);  // Set second as negative zero

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_value_decimals_is_equal_e) {
  DL_decimal first = {{0, 2, 4, 34}};
  DL_decimal second = {{0, 2, 4, 34}};

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_values_with_different_sign_is_not_equal_e) {
  DL_decimal first = {{0, 2, 4, 34}};
  DL_decimal second = {{0, 2, 4, 34}};
  DL_set_dec_sign(&second, 1);

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(same_values_different_scale_is_equal_e) {
  DL_decimal first = {{0, 0xffffffff, 0, 0}};
  DL_decimal second = {{0, 0xfffe7960, 0x1869f, 0x50000}};  // scale 5

  int res = DL_is_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

// is_not_equal

START_TEST(positive_zero_and_negative_zero_ne) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&second, 1);

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(positive_zero_and_positive_zero_ne) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(negative_zero_and_negative_zero_ne) {
  DL_decimal first = DL_DECIMAL_NULL;
  DL_decimal second = DL_DECIMAL_NULL;
  DL_set_dec_sign(&first, 1);
  DL_set_dec_sign(&second, 1);

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(same_value_decimals_ne) {
  DL_decimal first = {{0, 2, 4, 34}};
  DL_decimal second = {{0, 2, 4, 34}};

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

START_TEST(same_values_with_different_sign_is_not_equal_ne) {
  DL_decimal first = {{0, 2, 4, 34}};
  DL_decimal second = {{0, 2, 4, 34}};
  DL_set_dec_sign(&second, 1);

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(different_values_ne) {
  DL_decimal first = {{0, 2, 4, 34}};
  DL_decimal second = {{0, 2, 25, 34}};

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_TRUE);
}
END_TEST

START_TEST(same_values_different_scale_is_equal_ne) {
  DL_decimal first = {{0, 0xffffffff, 0, 0}};
  DL_decimal second = {{0, 0xfffe7960, 0x1869f, 0x50000}};  // scale 5

  int res = DL_is_not_equal(first, second);

  ck_assert_int_eq(res, DL_FALSE);
}
END_TEST

void srunner_add_compare_tests(SRunner *sr) {
  Suite *save_v3 = suite_create("Compare");
  TCase *tc_compare = tcase_create("Compare");
  suite_add_tcase(save_v3, tc_compare);

  // is_less
  tcase_add_test(tc_compare, DL_less_test_1);
  tcase_add_test(tc_compare, positive_zero_and_positive_zero);
  tcase_add_test(tc_compare, positive_zero_and_negative_zero);
  tcase_add_test(tc_compare, first_less_then_second);
  tcase_add_test(tc_compare, second_less_then_first);
  tcase_add_test(tc_compare, first_less_negative_sign);
  tcase_add_test(tc_compare, equal);
  tcase_add_test(tc_compare, same_value_different_scale_first_less);
  tcase_add_test(tc_compare, same_all_first_less);
  tcase_add_test(tc_compare, same_all_second_less);

  // is_less_or_equal
  tcase_add_test(tc_compare, positive_zero_and_positive_zero_le);
  tcase_add_test(tc_compare, positive_zero_and_negative_zero_le);
  tcase_add_test(tc_compare, first_less_then_second_le);
  tcase_add_test(tc_compare, second_less_then_first_le);
  tcase_add_test(tc_compare, first_less_negative_sign_le);
  tcase_add_test(tc_compare, equal_le);
  tcase_add_test(tc_compare, same_value_different_scale_first_less_le);
  tcase_add_test(tc_compare, same_all_first_less_le);
  tcase_add_test(tc_compare, same_all_second_less_le);
  // is_greater
  tcase_add_test(tc_compare, positive_zero_and_negative_zero_gr);
  tcase_add_test(tc_compare, first_greater_then_second_gr);
  tcase_add_test(tc_compare, first_less_then_second_gr);
  tcase_add_test(tc_compare, value_equal_first_positive_second_negative_gr);
  tcase_add_test(tc_compare,
                 first_value_less_first_scale_less_first_greater_gr);
  tcase_add_test(tc_compare, first_value_less_first_negative_gr);
  tcase_add_test(tc_compare,
                 first_value_less_first_negative_second_negative_gr);

  // is_greater_or_equal
  tcase_add_test(tc_compare, DL_is_greater_or_equal_0);

  tcase_add_test(tc_compare, positive_zero_and_negative_zero_ge);
  tcase_add_test(tc_compare, first_greater_then_second_ge);
  tcase_add_test(tc_compare, first_less_then_second_ge);
  tcase_add_test(tc_compare, value_equal_first_positive_second_negative_ge);
  tcase_add_test(tc_compare,
                 first_value_less_first_scale_less_first_greater_ge);
  tcase_add_test(tc_compare, first_value_less_first_negative_ge);
  tcase_add_test(tc_compare,
                 first_value_less_first_negative_second_negative_ge);

  // is_equal
  tcase_add_test(tc_compare, positive_zero_equal_other_positive_zero_e);
  tcase_add_test(tc_compare, negative_zero_equal_other_negative_zero_e);
  tcase_add_test(tc_compare, positive_zero_equal_negative_zero_e);
  tcase_add_test(tc_compare, same_value_decimals_is_equal_e);
  tcase_add_test(tc_compare, same_values_with_different_sign_is_not_equal_e);
  tcase_add_test(tc_compare, same_values_different_scale_is_equal_e);

  // is_not_equal
  tcase_add_test(tc_compare, positive_zero_and_negative_zero_ne);
  tcase_add_test(tc_compare, positive_zero_and_positive_zero_ne);
  tcase_add_test(tc_compare, negative_zero_and_negative_zero_ne);
  tcase_add_test(tc_compare, same_value_decimals_ne);
  tcase_add_test(tc_compare, same_values_with_different_sign_is_not_equal_ne);
  tcase_add_test(tc_compare, different_values_ne);
  tcase_add_test(tc_compare, same_values_different_scale_is_equal_ne);

  srunner_add_suite(sr, save_v3);
}
