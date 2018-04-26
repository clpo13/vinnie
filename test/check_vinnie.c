// Vinnie - simple VIN decoder
// Copyright (c) 2018 Cody Logan
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
 * Test that good VINs are accepted and bad VINs aren't.
 */
START_TEST (test_validate)
{
  char *goodVin = "1HGBH41JXMN109186";
  char *badVin = "2HGBH41JXMN109186";
  ck_assert_int_eq(validate(goodVin), 1);
  ck_assert_int_eq(validate(badVin), 0);
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
