#ifndef DL_DEC_TESTS_H_
#define DL_DEC_TESTS_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../DL_decimal.h"

#define SIGN_MASK 0x80000000
#define DL_TRUE 1
#define DL_FALSE 0
#define DL_DECIMAL_NULL {0};

void srunner_add_math_tests(SRunner *sr);
void srunner_add_others_tests(SRunner *sr);
void srunner_add_compare_tests(SRunner *sr);
void srunner_add_convert_tests(SRunner *sr);

void DL_create_test(SRunner *sr);
void DL_sign_test(SRunner *sr);
void DL_scale_factor_test(SRunner *sr);

#endif