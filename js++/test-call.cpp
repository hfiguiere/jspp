/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <memory>
#include <jsapi.h>

#include "runtime.hpp"
#include "context.hpp"

int main (int argc, char **argv)
{
  // get runtime
  jspp::Runtime& rt = jspp::Runtime::getRuntime();

  // get context
  std::unique_ptr<jspp::Context> ctx(rt.newContext());
  if (!ctx) {
    fprintf(stderr, "failed to get context");
    return 1;
  }

  ctx->initialize();
  // execute these:
  JS::Value val;


  if (!ctx->evaluateScript("function plustwo(v) { return v+2; }", &val)) {
    fprintf(stderr, "%d: Evaluate failed\n", __LINE__);
    return 1;
  }

  fprintf(stderr, "%d: calling plustwo(40)\n", __LINE__);
  ctx->call<1>("plustwo", &val, 40);

  if (!JSVAL_IS_NUMBER(val)) {
    fprintf(stderr, "%d: not a number\n", __LINE__);
    return 1;
  }

  if (!JSVAL_IS_INT(val)) {
    fprintf(stderr, "%d: not an int\n", __LINE__);
    return 1;
  }

  int32_t num = JSVAL_TO_INT(val);
  if (num != 42) {
    fprintf(stderr, "%d: wrong value. Expected 42, got %d\n", __LINE__, num);
    return 1;
  }

  fprintf(stderr, "calling plustwo(40.0)\n");
  ctx->call<1>("plustwo", &val, 40.0);
  if (!JSVAL_IS_NUMBER(val)) {
    fprintf(stderr, "%d: not a number\n", __LINE__);
    return 1;
  }

  if (JSVAL_TO_INT(val) != 42) {
    fprintf(stderr, "%d: wrong value. Expected 42, got %d\n", __LINE__, JSVAL_TO_INT(val));
    return 1;
  }

  if (!ctx->evaluateScript("function fortytwo() { return 42; }", &val)) {
    fprintf(stderr, "%d: Evaluate failed\n", __LINE__);
    return 1;
  }

  fprintf(stderr, "calling fortytwo()\n");
  ctx->call<0>("fortytwo", &val);
  if (!JSVAL_IS_NUMBER(val)) {
    fprintf(stderr, "%d: not a number\n", __LINE__);
    return 1;
  }

  if (JSVAL_TO_INT(val) != 42) {
    fprintf(stderr, "%d: wrong value. Expected 42, got %d\n", __LINE__,
            JSVAL_TO_INT(val));
    return 1;
  }

  return 0;
}
