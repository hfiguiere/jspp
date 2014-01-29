/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <string>

#include <jsapi.h>

#include "context.hpp"
#include "runtime.hpp"

namespace jspp {

/* The class of the global object. */
static JSClass global_class = { "global",
                                JSCLASS_NEW_RESOLVE | JSCLASS_GLOBAL_FLAGS,
                                JS_PropertyStub,
                                JS_DeletePropertyStub,
                                JS_PropertyStub,
                                JS_StrictPropertyStub,
                                JS_EnumerateStub,
                                JS_ResolveStub,
                                JS_ConvertStub,
                                nullptr,
                                JSCLASS_NO_OPTIONAL_MEMBERS
};

Context::Context(const Runtime* rt)
  : _jsctx(JS_NewContext(rt->js(), 8192))
  , _global(nullptr)
{
}

/* The error reporter callback. */
static void reportError(JSContext *cx, const char *message,
                        JSErrorReport *report)
{
  fprintf(stderr, "%s:%u:%s\n",
          report->filename ? report->filename : "[no filename]",
          (unsigned int) report->lineno,
          message);
}

bool Context::initialize()
{
  JS_SetErrorReporter(_jsctx, reportError);

  /* Enter a request before running anything in the context */
  JSAutoRequest ar(_jsctx);

  /* Create the global object in a new compartment. */
  _global = JS_NewGlobalObject(_jsctx, &global_class, nullptr);
  if (_global)
    return false;

  /* Set the context's global */
  JSAutoCompartment ac(_jsctx, _global);
  JS_SetGlobalObject(_jsctx, _global);

  /* Populate the global object with the standard globals, like Object and Array. */
  if (!JS_InitStandardClasses(_jsctx, _global)) {
    return false;
  }

  return true;
}

bool Context::evaluateScript(const char* script, JS::Value* val)
{
  JSAutoCompartment ac(_jsctx, _global);
  return JS_EvaluateScript(_jsctx, _global,
                           script, strlen(script),
                           "inline", 1, val);
}

bool Context::realCall(const char* fn, int n, JS::Value* args,
                       JS::Value* val) const
{
  JSAutoCompartment ac(_jsctx, _global);
  bool ok = JS_CallFunctionName(_jsctx, _global, fn, n, args, val);

  return ok;
}

template<>
bool Context::call<0>(const char* fn, JS::Value* val)
{
  return realCall(fn, 0, nullptr, val);
}

template <>
void Context::ToJSArg<int>(JS::Value *val, const int & arg) const
{
  *val = INT_TO_JSVAL(arg);
}

template <>
void Context::ToJSArg<double>(JS::Value *val, const double & arg) const
{
  *val = DOUBLE_TO_JSVAL(arg);
}

template <>
void Context::ToJSArg<const char*>(JS::Value *val,
                                   const char* const & arg) const
{
  *val = STRING_TO_JSVAL(JS_NewStringCopyZ(_jsctx, arg));
}

template <>
void Context::ToJSArg<std::string>(JS::Value *val,
                                   const std::string & arg) const
{
  *val = STRING_TO_JSVAL(JS_NewStringCopyZ(_jsctx, arg.c_str()));
}

} // ns jspp
