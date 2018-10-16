#pragma once
#include <object.hpp>
#include <null_object.hpp>
#include <map>
#include <memory>

struct Environment
{
  std::map<String, ObjectPtr> store;

  ObjectPtr Get(String key) {
    if (store.find(key) != store.end())
      return store[key];
    else
      return std::make_shared<NullObject>();
  }

  void Set(String key, ObjectPtr value) {
    if (store.find(key) != store.end())
      store[key] = value;
    else
      store.insert(std::make_pair(key, value));
  }

};

typedef std::shared_ptr<Environment> EnvironmentPtr;