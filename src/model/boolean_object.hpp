#pragma once
#include <object.hpp>

struct BooleanObject : Object
{
  bool value;
  explicit BooleanObject(bool value) : Object(BOOLEAN), value(value) {}

  String Inspect() override {
    return value > 0 ? "true" : "false";
  }
};