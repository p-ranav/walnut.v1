#pragma once
#include <object.hpp>
#include <null_object.hpp>
#include <map>
#include <memory>

struct Environment
{
  std::map<String, ObjectPtr> store;
  std::shared_ptr<Environment> outer;

  explicit Environment(std::shared_ptr<Environment> outer = nullptr) : store({}), outer(outer) {}

  ObjectPtr Get(String key) {
    ObjectPtr result;
    if (store.find(key) != store.end())
      result = store[key];
    else
      result = std::make_shared<NullObject>();

    if (result->type == ObjectType::NULL_ && outer != nullptr)
      result = outer->Get(key);

    return result;
  }

  void Set(String key, ObjectPtr value) {
    if (store.find(key) != store.end())
      store[key] = value;
    else
      store.insert(std::make_pair(key, value));
  }

};

typedef std::shared_ptr<Environment> EnvironmentPtr;