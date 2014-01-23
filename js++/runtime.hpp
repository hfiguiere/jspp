/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

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
