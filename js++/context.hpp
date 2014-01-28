/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <jsapi.h>

namespace jspp {

class Runtime;

class Context
{
public:
  Context(const Runtime* rt);

  bool initialize();
  JSContext* js() const
    { return _jsctx; }
  bool evaluateScript(const char* script, JS::Value* val);

  template <int N, typename... Args>
  bool call(const char* function, JS::Value* val, const Args&... args);

  friend class AutoCompartment;
private:

  template <typename Arg>
  void pushArg(JS::Value *args, const Arg & arg);

  template <typename Arg, typename... Args>
  void pushArg(JS::Value *args, size_t count,
               const Arg & arg, const Args&... otherArgs);

  JSContext* _jsctx;
  JSObject* _global;
};

template <typename T>
void ToJSArg(JS::Value *val, const T & arg);

template <typename Arg, typename... Args>
void Context::pushArg(JS::Value *args, size_t count,
                      const Arg & arg1, const Args&... otherArgs)
{
  pushArg(args, arg1);
  if (count > 1) {
    pushArg(args + 1, count - 1, otherArgs...);
  }
}

template <typename Arg>
void Context::pushArg(JS::Value *args, const Arg & arg1)
{
  ToJSArg(args, arg1);
}

template<int N, typename... Args>
bool Context::call(const char* fn, JS::Value* val, const Args&... args)
{
  JS::Value jsArgs[N];

  pushArg(jsArgs, args...);

  JSAutoCompartment ac(_jsctx, _global);
  bool ok = JS_CallFunctionName(_jsctx, _global, fn, N, jsArgs, val);

  return ok;
}

class AutoCompartment
{
public:
  AutoCompartment(Context* c)
    : _ac(c->_jsctx, c->_global)
    { }
private:
  JSAutoCompartment _ac;
};

}
