#pragma once
#include <object.hpp>
#include <null_object.hpp>
#include <map>
#include <memory>

namespace walnut
{

struct Environment
{
  std::map<String, ObjectPtr> store;

  typedef std::shared_ptr<Environment> EnvironmentPtr;
  EnvironmentPtr outer;

  explicit Environment(EnvironmentPtr outer_environment = nullptr) : store({}),
                                                                     outer(outer_environment) {}

  ~Environment()
  {
    store.clear();
    outer.reset();
  }

  std::shared_ptr<Environment> Copy()
  {
    std::shared_ptr<Environment> result = std::make_shared<Environment>();
    for (auto &kv : store)
    {
      result->Set(kv.first, kv.second->Copy());
    }
    if (outer != nullptr)
      result->outer = outer->Copy();
    return result;
  }

  ObjectPtr Get(String key)
  {
    ObjectPtr result;
    if (store.find(key) != store.end())
      result = store[key];
    else
      result = nullptr;

    if (result == nullptr && outer != nullptr)
      result = outer->Get(key);

    return result;
  }

  void Set(String key, ObjectPtr value)
  {
    if (store.find(key) != store.end())
      store[key] = value;
    else
      store.insert(std::make_pair(key, value));
  }
};

typedef std::shared_ptr<Environment> EnvironmentPtr;

} // namespace walnut