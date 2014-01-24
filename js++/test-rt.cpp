/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <memory>
#include <jsapi.h>

#include "runtime.hpp"
#include "context.hpp"

/* The error reporter callback. */
void reportError(JSContext *cx, const char *message, JSErrorReport *report) {
  fprintf(stderr, "%s:%u:%s\n",
          report->filename ? report->filename : "[no filename]",
          (unsigned int) report->lineno,
          message);
}

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

  JS_SetErrorReporter(ctx->js(), reportError);
  ctx->initialize();
  // execute these:
  JS::Value val;

  if (!ctx->evaluateScript("2 + 2;", &val)) {
    fprintf(stderr, "Evaluate failed\n");
    return 1;
  }

  if (!JSVAL_IS_NUMBER(val)) {
    fprintf(stderr, "not a number\n");
    return 1;
  }

  if (JSVAL_TO_INT(val) != 4) {
    fprintf(stderr, "wrong value. Expected 4, got %d\n", JSVAL_TO_INT(val));
    return 1;
  }

  return 0;
}
