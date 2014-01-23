/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "binder.hpp"

namespace jspp {

PropertyBase::PropertyBase(BinderBase* binder, const char* name)
  : m_name(name)
{
  binder->add(name, this);
}

BinderBase::BinderBase(const char* cname)
  : m_classname(cname)
{
}

void BinderBase::add(const char* name, PropertyBase* prop)
{
  m_props.insert(std::make_pair(name, prop));
}

}
