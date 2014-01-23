
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
