#pragma once

#include <functional>
#include <map>
#include <string>

#include "context.hpp"

#define JSB_PROP_VAR(p, c) p##c

#define JSB_PROPERTY_RW(t, p, g, s)		\
  new jspp::Property<t>(this, #p, g, s);

#define JSB_PROPERTY_RO(t, p, g)			\
  new jspp::Property<t>(this, #p, g);

namespace jspp {

class BinderBase;

class PropertyBase
{
public:
  PropertyBase(BinderBase* binder, const char* name);
private:
  std::string m_name;
};

template <class T>
class Property
  : public PropertyBase
{
public:
  Property(BinderBase* binder, const char* name,
           std::function<std::string(T*)> g,
           std::function<void(T*,std::string)> = nullptr)
    : PropertyBase(binder, name)
    {
    }
};


class BinderBase
{
public:
  BinderBase(const char* cname);
  void add(const char*, PropertyBase*);
private:
  std::string m_classname;
  std::map<std::string, PropertyBase*> m_props;
};


// Bind C++ class
// Singleton PER type T
template <class T>
class Binder
  : public BinderBase
{
public:
  Binder(const char* cname)
    : BinderBase(cname)
    {
    }
  static const Binder<T>* get_instance()
    {
      return _instance;
    }
private:
  static Binder<T>* _instance;
};

template <class T>
Binder<T>* Binder<T>::_instance = nullptr;

// Wrap an object instance
template <class T>
class Wrap
{
public:
  Wrap(T* s, Context* ctx)
    : self(s)
    , binder(Binder<T>::get_instance())
    , _ctx(ctx)
    { }

  T * self;
  const Binder<T> * binder;
private:
  Context* _ctx;
};

}
