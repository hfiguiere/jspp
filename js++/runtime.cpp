
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
