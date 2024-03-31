#include "DL_test.h"

START_TEST(set_zero) {  // [s0000000ffffffff0000000000000000]
  DL_decimal dec1t1 = {{6, 0, 0, 0b10000000000000000000000000000000}},
             dec2t1 = {0};
  DL_decimal dec1t2 = {{0, 0, 0, 0b00000000000000000000000000000000}},
             dec2t2 = {0};
  DL_decimal dec1t3 = {{0, 4, 0, 0b00000000000001010000000000000000}},
             dec2t3 = {{0, 0, 0, 0b00000000000001010000000000000000}};
  DL_decimal dec1t4 = {{0, 0, 0, 0b10000000000001010000000000000000}},
             dec2t4 = {{0, 0, 0, 0b00000000000001010000000000000000}};

  DL_set_dec_sign(&dec1t1, 0);
  DL_set_dec_sign(&dec1t2, 0);
  DL_set_dec_sign(&dec1t3, 0);
  DL_set_dec_sign(&dec1t4, 0);

  ck_assert_int_eq(dec1t1.bits[3], dec2t1.bits[3]);
  ck_assert_int_eq(dec1t2.bits[3], dec2t2.bits[3]);
  ck_assert_int_eq(dec1t3.bits[3], dec2t3.bits[3]);
  ck_assert_int_eq(dec1t4.bits[3], dec2t4.bits[3]);
}
END_TEST

START_TEST(set_one) {  // [s0000000ffffffff0000000000000000]
  DL_decimal dec1t1 = {{0, 0, 0, 0b10000000000000000000000000000000}},
             dec2t1 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  DL_decimal dec1t2 = {{0, 3, 0, 0b00000000000000000000000000000000}},
             dec2t2 = {{0, 0, 0, 0b10000000000000000000000000000000}};
  DL_decimal dec1t3 = {{0, 0, 0, 0b00000000000001010000000000000000}},
             dec2t3 = {{0, 0, 0, 0b10000000000001010000000000000000}};
  DL_decimal dec1t4 = {{0, 0, 0, 0b10000000000001010000000000000000}},
             dec2t4 = {{0, 0, 0, 0b10000000000001010000000000000000}};

  DL_set_dec_sign(&dec1t1, 1);
  DL_set_dec_sign(&dec1t2, 1);
  DL_set_dec_sign(&dec1t3, 1);
  DL_set_dec_sign(&dec1t4, 1);

  ck_assert_int_eq(dec1t1.bits[3], dec2t1.bits[3]);
  ck_assert_int_eq(dec1t2.bits[3], dec2t2.bits[3]);
  ck_assert_int_eq(dec1t3.bits[3], dec2t3.bits[3]);
  ck_assert_int_eq(dec1t4.bits[3], dec2t4.bits[3]);
}
END_TEST

START_TEST(set_error) {  // [s0000000ffffffff0000000000000000]
  DL_decimal dec1t1 = {{3, 0, 0, 0b10000000000000000000000000000000}};
  DL_decimal dec1t2 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  DL_decimal dec1t3 = {{0, 0, 0, 0b00000000000001010000000000000000}};
  DL_decimal dec1t4 = {{0, 0, 0, 0b10000000000001010000000000000000}};

  ck_assert_int_eq(DL_set_dec_sign(&dec1t1, -20), 1);
  ck_assert_int_eq(DL_set_dec_sign(&dec1t2, 5), 1);
  ck_assert_int_eq(DL_set_dec_sign(&dec1t3, 7), 1);
  ck_assert_int_eq(DL_set_dec_sign(&dec1t4, 0), 0);
}
END_TEST

START_TEST(get_zero) {
  DL_decimal dect1 = {{0, 21, 0, 0b00000000000000000000000000000000}},
             dect2 = {{0, 0, 0, 0b00000000000001010000000000000000}},
             dect3 = {{0, 0, 0, 0b00000000000011010000000000000000}},
             dect4 = {{0, 0, 0, 0b00000000000001010000000000000000}},
             dect5 = {{0, 0, 0, 0b00000000000000000000000000000000}};
  int signt1, signt2, signt3, signt4, signt5;

  DL_get_dec_sign(dect1, &signt1);
  DL_get_dec_sign(dect2, &signt2);
  DL_get_dec_sign(dect3, &signt3);
  DL_get_dec_sign(dect4, &signt4);
  DL_get_dec_sign(dect5, &signt5);

  ck_assert_int_eq(signt1, 0);
  ck_assert_int_eq(signt2, 0);
  ck_assert_int_eq(signt3, 0);
  ck_assert_int_eq(signt4, 0);
  ck_assert_int_eq(signt5, 0);
}
END_TEST

START_TEST(get_one) {
  DL_decimal dect1 = {{0, 0, 0, 0b10000000000000000000000000000000}},
             dect2 = {{0, 0, 0, 0b10000000000001010000000000000000}},
             dect3 = {{0, 0, 0, 0b10000000000011010000000000000000}},
             dect4 = {{0, 0, 0, 0b10000000000001010000000000000000}},
             dect5 = {{0, 0, 0, 0b10000000000000100000000000000000}};
  int signt1, signt2, signt3, signt4, signt5;

  DL_get_dec_sign(dect1, &signt1);
  DL_get_dec_sign(dect2, &signt2);
  DL_get_dec_sign(dect3, &signt3);
  DL_get_dec_sign(dect4, &signt4);
  DL_get_dec_sign(dect5, &signt5);

  ck_assert_int_eq(signt1, 1);
  ck_assert_int_eq(signt2, 1);
  ck_assert_int_eq(signt3, 1);
  ck_assert_int_eq(signt4, 1);
  ck_assert_int_eq(signt5, 1);
}
END_TEST

void DL_sign_test(SRunner *sr) {
  Suite *suite = suite_create("dec_signs_test");
  TCase *tcase_set = tcase_create("dec_set_sign");
  TCase *tcase_get = tcase_create("dec_get_sign");

  tcase_add_test(tcase_set, set_zero);
  tcase_add_test(tcase_set, set_one);
  tcase_add_test(tcase_set, set_error);

  tcase_add_test(tcase_get, get_zero);
  tcase_add_test(tcase_get, get_one);

  suite_add_tcase(suite, tcase_set);
  suite_add_tcase(suite, tcase_get);

  srunner_add_suite(sr, suite);
}
