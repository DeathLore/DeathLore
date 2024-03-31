#include "DL_test.h"

//[s0000000ffffffff0000000000000000]

START_TEST(set_scale) {  //[s0000000ffffffff0000000000000000]
  DL_decimal dec1t1 = {{0, 0, 0, 0b00000000000111000000000000000000}},
             dec2t1 = {0};
  DL_decimal dec1t2 = {{0, 3, 0, 0b10000000000000000000000000000000}},
             dec2t2 = {{0, 3, 0, 0b10000000000110010000000000000000}};
  DL_decimal dec1t3 = {{0, 5, 0, 0b10000000000110010000000000000000}},
             dec2t3 = {{0, 5, 0, 0b10000000000000000000000000000000}};
  DL_decimal dec1t4 = {{7, 0, 0, 0b00000000000011100000000000000000}},
             dec2t4 = {{7, 0, 0, 0b00000000000110010000000000000000}};

  DL_set_dec_scale_factor(&dec1t1, 0);
  DL_set_dec_scale_factor(&dec1t2, 25);
  DL_set_dec_scale_factor(&dec1t3, 0);
  DL_set_dec_scale_factor(&dec1t4, 25);

  ck_assert_int_eq(dec1t1.bits[3], dec2t1.bits[3]);
  ck_assert_int_eq(dec1t2.bits[3], dec2t2.bits[3]);
  ck_assert_int_eq(dec1t3.bits[3], dec2t3.bits[3]);
  ck_assert_int_eq(dec1t4.bits[3], dec2t4.bits[3]);
}
END_TEST

START_TEST(set_error) {
  DL_decimal dec1t1 = {{1, 0, 0, 0b00000000000111000000000000000000}},
             dec1t2 = {{0, 0, 0, 0b10000000000000000000000000000000}},
             dec1t3 = {{0, 1, 0, 0b10000000000110010000000000000000}},
             dec1t4 = {{0, 0, 3, 0b10000000000110010000000000000000}},
             dec1t5 = {{2, 2, 0, 0b10000000000110010000000000000000}};

  ck_assert_int_eq(DL_set_dec_scale_factor(&dec1t1, 29), 1);
  ck_assert_int_eq(DL_set_dec_scale_factor(&dec1t2, -23), 1);
  ck_assert_int_eq(DL_set_dec_scale_factor(&dec1t3, 100), 1);
  ck_assert_int_eq(DL_set_dec_scale_factor(&dec1t4, -1), 1);
  ck_assert_int_eq(DL_set_dec_scale_factor(&dec1t5, 3), 0);
}
END_TEST

START_TEST(get_scale) {
  DL_decimal dec1t1 = {{1, 0, 0, 0b00000000000111000000000000000000}},
             dec1t2 = {{0, 0, 0, 0b10000000000000000000000000000000}},
             dec1t3 = {{0, 1, 0, 0b10000000000110010000000000000000}},
             dec1t4 = {{0, 0, 3, 0b10000000000000010000000000000000}},
             dec1t5 = {{2, 2, 0, 0b10000000000110010000000000000000}};
  int scale1, scale2, scale3, scale4, scale5;
  DL_get_dec_scale_factor(dec1t1, &scale1);
  DL_get_dec_scale_factor(dec1t2, &scale2);
  DL_get_dec_scale_factor(dec1t3, &scale3);
  DL_get_dec_scale_factor(dec1t4, &scale4);
  DL_get_dec_scale_factor(dec1t5, &scale5);

  ck_assert_int_eq(scale1, 28);
  ck_assert_int_eq(scale2, 0);
  ck_assert_int_eq(scale3, 25);
  ck_assert_int_eq(scale4, 1);
  ck_assert_int_eq(scale5, 25);
}
END_TEST

void DL_scale_factor_test(SRunner *sr) {
  Suite *suite = suite_create("dec_scale_factor_test");
  TCase *tcase_set = tcase_create("dec_set_scale_factor");
  TCase *tcase_get = tcase_create("dec_get_scale_factor");

  tcase_add_test(tcase_set, set_scale);
  tcase_add_test(tcase_set, set_error);

  tcase_add_test(tcase_get, get_scale);

  suite_add_tcase(suite, tcase_set);
  suite_add_tcase(suite, tcase_get);

  srunner_add_suite(sr, suite);
}