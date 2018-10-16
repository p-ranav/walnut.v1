#pragma once
#include <object.hpp>
#include <memory>

struct BooleanObject : Object
{
  bool value;
  explicit BooleanObject(bool value) : Object(BOOLEAN), value(value) {}

  String Inspect() override {
    return (value == true) ? "true" : "false";
  }
};

typedef std::shared_ptr<BooleanObject> BooleanObjectPtr;