/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <jsapi.h>
#include "runtime.hpp"
#include "context.hpp"

namespace jspp {

Runtime& Runtime::getRuntime()
{
  static Runtime* rt = new Runtime;
  return *rt;
}

Runtime::Runtime()
  : _jsrt(JS_NewRuntime(8L * 1024L * 1024L, JS_NO_HELPER_THREADS))
{
}

Context* Runtime::newContext()
{
  return new Context(this);
}

}
