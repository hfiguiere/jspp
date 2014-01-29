/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>

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

  template <typename T>
  T FromJSArg(const JS::Value &val) const;

  friend class AutoCompartment;
private:
  bool realCall(const char* fn, int n, JS::Value* args,
                JS::Value* val) const;

  template <typename Arg>
  void pushArg(JS::Value *args, const Arg & arg) const;

  template <typename Arg, typename... Args>
  void pushArgs(JS::Value *args, size_t count,
               const Arg & arg, const Args&... otherArgs) const;
  template <typename Arg>
  void pushArgs(JS::Value *args, size_t count,
                const Arg & arg1) const;

  void ToJSArg(JS::Value *val, int arg) const;
  void ToJSArg(JS::Value *val, double arg) const;
  void ToJSArg(JS::Value *val, const char* arg) const;
  void ToJSArg(JS::Value *val, const std::string & arg) const;

  JSContext* _jsctx;
  JSObject* _global;
};

template <typename Arg, typename... Args>
void Context::pushArgs(JS::Value *args, size_t count,
                      const Arg & arg1, const Args&... otherArgs) const
{
  pushArg(args, arg1);
  if (count > 1) {
    pushArgs(args + 1, count - 1, otherArgs...);
  }
}

template <typename Arg>
void Context::pushArgs(JS::Value *args, size_t count,
                       const Arg & arg1) const
{
  pushArg(args, arg1);
}

template <typename Arg>
void Context::pushArg(JS::Value *args, const Arg & arg1) const
{
  ToJSArg(args, arg1);
}

template<>
bool Context::call<0>(const char* fn, JS::Value* val);

template<int N, typename... Args>
bool Context::call(const char* fn, JS::Value* val, const Args&... args)
{
  JS::Value jsArgs[N];

  pushArgs(jsArgs, N, args...);

  return realCall(fn, N, jsArgs, val);
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
