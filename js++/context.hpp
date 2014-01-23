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
