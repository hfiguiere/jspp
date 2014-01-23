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

  friend class AutoCompartment;
private:
  JSContext* _jsctx;
  JSObject* _global;
};

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
