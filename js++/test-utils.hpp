#pragma once

#define TEST_OUT(x, ...)                                                 \
  test_print(x,  __FUNCTION__, __FILE__, __LINE__, ## __VA_ARGS__)


/** print error message. printf format.
 * Call with the TEST_OUT macro.
 * @param fmt the formt string, printf style
 * @param func the func name
 */
void test_print(const char *fmt, const char* func, const char* filen,
               int linen, ...)
  __attribute__ ((format (printf, 1, 5)));


