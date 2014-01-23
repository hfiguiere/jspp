#pragma once

struct JSRuntime;

namespace jspp {

class Context;

class Runtime
{
public:
  static Runtime& getRuntime();
  Context* newContext();

  JSRuntime* js() const
    { return _jsrt; }
private:
  Runtime();

  JSRuntime* _jsrt;
};

}
