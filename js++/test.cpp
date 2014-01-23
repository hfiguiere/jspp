/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <jsapi.h>

#include "binder.hpp"
#include "runtime.hpp"
#include "context.hpp"

class TestObject
{
public:
  std::string foo() const
    { return "Foo"; }
  std::string bar() const
    { return m_bar; }
  void set_bar(const std::string &v)
    { m_bar = v; }
private:
  std::string m_bar;
};


class TestObjectBinder
  : public jspp::Binder<TestObject>
{
public:
  TestObjectBinder()
    : jspp::Binder<TestObject>("TestObject")
    {
      JSB_PROPERTY_RO(TestObject, foo, &TestObject::foo);
      JSB_PROPERTY_RW(TestObject, bar, &TestObject::bar,
                      &TestObject::set_bar);
    }
};

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
  jspp::Context* ctx = rt.newContext();
  if (!ctx) {
    return 1;
  }

  JS_SetErrorReporter(ctx->js(), reportError);
  ctx->initialize();
  // execute these:
  JS::Value val;
#if 0
  const char* script1 = "TestObject.foo;";
  if (ctx->evaluateScript(script1, &val)) {
    // error
  }

  const char* script2 = "TestObject.bar = 'doh'; return TestObject.bar;";
  if (ctx->evaluateScript(script2, &val)) {
    // error
  }
#endif

  if (ctx->evaluateScript("2 + 2;", &val)) {
    if (!JSVAL_IS_NUMBER(val)) {
      printf("not a number\n");
    }
    else {
      printf("Number is %d\n", JSVAL_TO_INT(val));
    }
  }
  else {
    printf("Evaluate failed\n");
  }

  delete ctx;

  return 0;
}
