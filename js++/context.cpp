/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

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

bool Context::initialize()
{
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

  /* Your application code here. This may include JSAPI calls to create your own custom JS objects and run scripts. */
  return true;
}

bool Context::evaluateScript(const char* script, JS::Value* val)
{
  JSAutoCompartment ac(_jsctx, _global);
  return JS_EvaluateScript(_jsctx, _global,
                           script, strlen(script),
                           "inline", 1, val);
}

}
