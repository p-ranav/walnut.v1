#pragma once
#include <object.hpp>

struct IntegerObject : Object
{
  int value;
  explicit IntegerObject(int value) : Object(INTEGER), value(value) {}
  
  String Inspect() override {
    return std::to_string(value);
  }
};

typedef std::shared_ptr<IntegerObject> IntegerObjectPtr;