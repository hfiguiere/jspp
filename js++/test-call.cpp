/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <memory>
#include <jsapi.h>

#include "runtime.hpp"
#include "context.hpp"
#include "test-utils.hpp"

int main (int argc, char **argv)
{
  // get runtime
  jspp::Runtime& rt = jspp::Runtime::getRuntime();

  // get context
  std::unique_ptr<jspp::Context> ctx(rt.newContext());
  if (!ctx) {
    TEST_OUT("failed to get context");
    return 1;
  }

  ctx->initialize();

  JS::Value val;
  int32_t num;
  double fnum;

  /* TEST 1: function call with one int argument */
  if (!ctx->evaluateScript("function plustwo(v) { return v+2; }", &val)) {
    TEST_OUT("Evaluate failed");
    return 1;
  }

  TEST_OUT("calling plustwo(40)");
  ctx->call<1>("plustwo", &val, 40);

  if (!JSVAL_IS_NUMBER(val)) {
    TEST_OUT("not a number");
    return 1;
  }

  if (!JSVAL_IS_INT(val)) {
    TEST_OUT("not an int");
    return 1;
  }

  num = ctx->FromJSArg<int32_t>(val);
  if (num != 42) {
    TEST_OUT("Wrong value. Expected 42, got %d", num);
    return 1;
  }

  /* TEST 2: function call with one float argument */
  TEST_OUT("calling plustwo(40.1)");
  ctx->call<1>("plustwo", &val, 40.1);
  if (!JSVAL_IS_NUMBER(val)) {
    TEST_OUT("not a number");
    return 1;
  }

  fnum = ctx->FromJSArg<double>(val);
  if (fnum != 42.1) {
    TEST_OUT("Wrong value. Expected 42.1, got %lf", fnum);
    return 1;
  }

  /* TEST 3: function call with non argument */
  if (!ctx->evaluateScript("function fortytwo() { return 42; }", &val)) {
    TEST_OUT("Evaluate failed");
    return 1;
  }

  TEST_OUT("calling fortytwo()");
  ctx->call<0>("fortytwo", &val);
  if (!JSVAL_IS_NUMBER(val)) {
    TEST_OUT("not a number");
    return 1;
  }

  if (JSVAL_TO_INT(val) != 42) {
    TEST_OUT("Wrong value. Expected 42, got %d", JSVAL_TO_INT(val));
    return 1;
  }

  /* TEST 4: function call with two arguments */
  if (!ctx->evaluateScript("function addtwo(a,b) { return a+b; }", &val)) {
    TEST_OUT("Evaluate failed");
    return 1;
  }

  TEST_OUT("calling addtwo()");
  ctx->call<2>("addtwo", &val, 20, 22);
  if (!JSVAL_IS_NUMBER(val)) {
    TEST_OUT("not a number");
    return 1;
  }

  if (JSVAL_TO_INT(val) != 42) {
    TEST_OUT("Wrong value. Expected 42, got %d", JSVAL_TO_INT(val));
    return 1;
  }

  /* TEST 5: function call with two string arguments returning a string*/
  if (!ctx->evaluateScript("function concat(a,b) { return a + ' ' + b; }",
                           &val)) {
    TEST_OUT("Evaluate failed");
    return 1;
  }

  TEST_OUT("calling concat()");
  ctx->call<2>("concat", &val, "forty", "two");
  if (!JSVAL_IS_STRING(val)) {
    TEST_OUT("not a string");
    return 1;
  }

  std::string str = ctx->FromJSArg<std::string>(val);
  if (str != "forty two") {
    TEST_OUT("expected string not found");
    return 1;
  }

  return 0;
}
