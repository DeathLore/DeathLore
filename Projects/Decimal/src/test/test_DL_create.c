#include "DL_test.h"

START_TEST(create_success) {
  DL_decimal t1dec1 = DL_create(0, 0, 0, 0, 0), t1dec2 = {0},
             t2dec1 = DL_create(0, 0, 0, 0, 2), t2dec2 = {{2, 0, 0, 0}},
             t3dec1 = DL_create(0, 0, 0, 4, 0), t3dec2 = {{0, 4, 0, 0}},
             t4dec1 = DL_create(0, 0, 0, 4, 5), t4dec2 = {{5, 4, 0, 0}},
             t5dec1 = DL_create(0, 0, 1, 0, 0), t5dec2 = {{0, 0, 1, 0}},
             t6dec1 = DL_create(0, 0, 5, 0, 7), t6dec2 = {{7, 0, 5, 0}},
             t7dec1 = DL_create(0, 0, 6, 1, 0), t7dec2 = {{0, 1, 6, 0}},
             t8dec1 = DL_create(0, 0, 3, 4, 7), t8dec2 = {{7, 4, 3, 0}},
             t9dec1 = DL_create(0, 2, 0, 0, 0), t9dec2 = {{0, 0, 0, 0}},
             t10dec1 = DL_create(0, 4, 0, 0, 1), t10dec2 = {{1, 0, 0, 0}},
             t11dec1 = DL_create(0, 7, 0, 6, 0), t11dec2 = {{0, 6, 0, 0}},
             t12dec1 = DL_create(0, 4, 0, 5, 3), t12dec2 = {{3, 5, 0, 0}},
             t13dec1 = DL_create(0, 20, 1, 0, 0), t13dec2 = {{0, 0, 1, 0}},
             t14dec1 = DL_create(0, 23, 3, 0, 4), t14dec2 = {{4, 0, 3, 0}},
             t15dec1 = DL_create(0, 23, 3, 4, 0), t15dec2 = {{0, 4, 3, 0}},
             t16dec1 = DL_create(0, 4, 545, 43, 6434),
             t16dec2 = {{6434, 43, 545, 0}}, t17dec1 = DL_create(1, 0, 0, 0, 0),
             t17dec2 = {{0, 0, 0, 0}}, t18dec1 = DL_create(1, 0, 0, 0, 435),
             t18dec2 = {{435, 0, 0, 0}}, t19dec1 = DL_create(1, 0, 0, 323, 0),
             t19dec2 = {{0, 323, 0, 0}}, t20dec1 = DL_create(1, 0, 0, 6, 432),
             t20dec2 = {{432, 6, 0, 0}}, t21dec1 = DL_create(1, 0, 55, 0, 0),
             t21dec2 = {{0, 0, 55, 0}}, t22dec1 = DL_create(1, 0, 54, 0, 34),
             t22dec2 = {{34, 0, 54, 0}}, t23dec1 = DL_create(1, 0, 45, 53, 0),
             t23dec2 = {{0, 53, 45, 0}}, t24dec1 = DL_create(1, 0, 34, 545, 45),
             t24dec2 = {{45, 545, 34, 0}}, t25dec1 = DL_create(1, 6, 0, 0, 0),
             t25dec2 = {{0, 0, 0, 0}}, t26dec1 = DL_create(1, 6, 0, 0, 4),
             t26dec2 = {{4, 0, 0, 0}}, t27dec1 = DL_create(1, 7, 0, 3, 0),
             t27dec2 = {{0, 3, 0, 0}}, t28dec1 = DL_create(1, 3, 0, 5, 3),
             t28dec2 = {{3, 5, 0, 0}}, t29dec1 = DL_create(1, 6, 43, 0, 0),
             t29dec2 = {{0, 0, 43, 0}},
             t30dec1 = DL_create(1, 21, 4345, 0, 3553),
             t30dec2 = {{3553, 0, 4345, 0}},
             t31dec1 = DL_create(1, 9, 245, 42, 0), t31dec2 = {{0, 42, 245, 0}},
             t32dec1 = DL_create(1, 5, 324, 35, 643),
             t32dec2 = {{643, 35, 324, 0}};

  DL_set_dec_scale_factor(&t9dec2, 2);
  DL_set_dec_scale_factor(&t10dec2, 4);
  DL_set_dec_scale_factor(&t11dec2, 7);
  DL_set_dec_scale_factor(&t12dec2, 4);
  DL_set_dec_scale_factor(&t13dec2, 20);
  DL_set_dec_scale_factor(&t14dec2, 23);
  DL_set_dec_scale_factor(&t15dec2, 23);
  DL_set_dec_scale_factor(&t16dec2, 4);
  DL_set_dec_scale_factor(&t25dec2, 6);
  DL_set_dec_scale_factor(&t26dec2, 6);
  DL_set_dec_scale_factor(&t27dec2, 7);
  DL_set_dec_scale_factor(&t28dec2, 3);
  DL_set_dec_scale_factor(&t29dec2, 6);
  DL_set_dec_scale_factor(&t30dec2, 21);
  DL_set_dec_scale_factor(&t31dec2, 9);
  DL_set_dec_scale_factor(&t32dec2, 5);

  DL_set_dec_sign(&t17dec2, 1);
  DL_set_dec_sign(&t18dec2, 1);
  DL_set_dec_sign(&t19dec2, 1);
  DL_set_dec_sign(&t20dec2, 1);
  DL_set_dec_sign(&t21dec2, 1);
  DL_set_dec_sign(&t22dec2, 1);
  DL_set_dec_sign(&t23dec2, 1);
  DL_set_dec_sign(&t24dec2, 1);
  DL_set_dec_sign(&t25dec2, 1);
  DL_set_dec_sign(&t26dec2, 1);
  DL_set_dec_sign(&t27dec2, 1);
  DL_set_dec_sign(&t28dec2, 1);
  DL_set_dec_sign(&t29dec2, 1);
  DL_set_dec_sign(&t30dec2, 1);
  DL_set_dec_sign(&t31dec2, 1);
  DL_set_dec_sign(&t32dec2, 1);

  ck_assert_int_eq(DL_is_equal(t1dec1, t1dec2), 1);
  ck_assert_int_eq(DL_is_equal(t2dec1, t2dec2), 1);
  ck_assert_int_eq(DL_is_equal(t3dec1, t3dec2), 1);
  ck_assert_int_eq(DL_is_equal(t4dec1, t4dec2), 1);
  ck_assert_int_eq(DL_is_equal(t5dec1, t5dec2), 1);
  ck_assert_int_eq(DL_is_equal(t6dec1, t6dec2), 1);
  ck_assert_int_eq(DL_is_equal(t7dec1, t7dec2), 1);
  ck_assert_int_eq(DL_is_equal(t8dec1, t8dec2), 1);
  ck_assert_int_eq(DL_is_equal(t9dec1, t9dec2), 1);
  ck_assert_int_eq(DL_is_equal(t10dec1, t10dec2), 1);
  ck_assert_int_eq(DL_is_equal(t11dec1, t11dec2), 1);
  ck_assert_int_eq(DL_is_equal(t12dec1, t12dec2), 1);
  ck_assert_int_eq(DL_is_equal(t13dec1, t13dec2), 1);
  ck_assert_int_eq(DL_is_equal(t14dec1, t14dec2), 1);
  ck_assert_int_eq(DL_is_equal(t15dec1, t15dec2), 1);
  ck_assert_int_eq(DL_is_equal(t16dec1, t16dec2), 1);
  ck_assert_int_eq(DL_is_equal(t17dec1, t17dec2), 1);
  ck_assert_int_eq(DL_is_equal(t18dec1, t18dec2), 1);
  ck_assert_int_eq(DL_is_equal(t19dec1, t19dec2), 1);
  ck_assert_int_eq(DL_is_equal(t20dec1, t20dec2), 1);
  ck_assert_int_eq(DL_is_equal(t21dec1, t21dec2), 1);
  ck_assert_int_eq(DL_is_equal(t22dec1, t22dec2), 1);
  ck_assert_int_eq(DL_is_equal(t23dec1, t23dec2), 1);
  ck_assert_int_eq(DL_is_equal(t24dec1, t24dec2), 1);
  ck_assert_int_eq(DL_is_equal(t25dec1, t25dec2), 1);
  ck_assert_int_eq(DL_is_equal(t26dec1, t26dec2), 1);
  ck_assert_int_eq(DL_is_equal(t27dec1, t27dec2), 1);
  ck_assert_int_eq(DL_is_equal(t28dec1, t28dec2), 1);
  ck_assert_int_eq(DL_is_equal(t29dec1, t29dec2), 1);
  ck_assert_int_eq(DL_is_equal(t30dec1, t30dec2), 1);
  ck_assert_int_eq(DL_is_equal(t31dec1, t31dec2), 1);
  ck_assert_int_eq(DL_is_equal(t32dec1, t32dec2), 1);
}
END_TEST

START_TEST(create_error) {
  DL_decimal testdecimal = {0}, ts1dec = DL_create(-20, 0, 0, 0, 0),
             ts2dec = DL_create(2, 0, 0, 0, 0),
             ts3dec = DL_create(-1, 0, 0, 43, 322),
             ts4dec = DL_create(70, 0, 43553, 0, 0),
             tf1dec = DL_create(0, 40, 0, 0, 0),
             tf2dec = DL_create(0, -3, 0, 0, 0),
             tf3dec = DL_create(0, 34, 435, 0, 532),
             tf4dec = DL_create(0, -4, 342, 0, 0),
             tsf1dec = DL_create(4, 4, 0, 0, 0),
             tsf2dec = DL_create(1, 43, 0, 0, 0),
             tsf3dec = DL_create(-20, 342, 0, 0, 0),
             tsf4dec = DL_create(-20, 6, 0, 3245, 532);

  ck_assert_int_eq(DL_is_equal(ts1dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(ts2dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(ts3dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(ts4dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tf1dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tf2dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tf3dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tf4dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tsf1dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tsf2dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tsf3dec, testdecimal), 1);
  ck_assert_int_eq(DL_is_equal(tsf4dec, testdecimal), 1);
}
END_TEST

void DL_create_test(SRunner* sr) {
  Suite* suite = suite_create("dec_create_func_test");
  TCase* tcase_create_successfully =
      tcase_create("decimal_was_created_successfully");
  TCase* tcase_create_error = tcase_create("decimal_creation_with_error");

  tcase_add_test(tcase_create_successfully, create_success);
  tcase_add_test(tcase_create_error, create_error);

  suite_add_tcase(suite, tcase_create_successfully);
  suite_add_tcase(suite, tcase_create_error);

  srunner_add_suite(sr, suite);
}