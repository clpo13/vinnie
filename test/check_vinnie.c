// Vinnie - simple VIN decoder
// Copyright (c) 2018-2019 Cody Logan
// SPDX-License-Identifier: MIT

#include <stdbool.h>
#include <stdlib.h>

#include <check.h>

#include "vin.h"

/**
 * Test that converting characters to numbers works.
 */
START_TEST (test_transliterate)
{
  char *vin = "1HGBH41JXMN109186";
  char c = vin[1];
  ck_assert_int_eq(transliterate(c), 8);
}
END_TEST

/**
 * Test that the proper check digit is returned (9th character).
 */
START_TEST (test_getCheckDigit)
{
  char *vin = "1HGBH41JXMN109186";
  ck_assert_int_eq(getCheckDigit(vin), vin[8]);
}
END_TEST

/**
 * @brief Test that good VINs are accepted and bad VINs aren't.
 * 
 * A good VIN is 17 digits and passes the check digit calculation.
 * A bad VIN is not 17 digits or fails to pass the check digit calculation.
 */
START_TEST (test_validate)
{
  char *goodVin = "1HGBH41JXMN109186";
  char *badVin = "2HGBH41JXMN109186";
  char *shortVin = "1HGBH41JXMN10918";
  ck_assert_int_eq(validate(goodVin), 1);
  ck_assert_int_eq(validate(badVin), 0);
  ck_assert_int_eq(validate(shortVin), 0);
}
END_TEST

/**
 * Create a test suite.
 */
Suite *vinnie_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Vinnie");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_transliterate);
  tcase_add_test(tc_core, test_getCheckDigit);
  tcase_add_test(tc_core, test_validate);
  suite_add_tcase(s, tc_core);

  return s;
}

/**
 * The main function collects the specified tests and creates a test runner to
 * execute them.
 * @return the number of failed tests
 */
int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = vinnie_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
