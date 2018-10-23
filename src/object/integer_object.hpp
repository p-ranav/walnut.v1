#pragma once
#include <object.hpp>
#include <double_object.hpp>

struct IntegerObject : Object
{
  int value;
  explicit IntegerObject(int value) : Object(INTEGER, false, true), value(value) {}

  ObjectPtr Copy() override
  {
    return std::make_shared<IntegerObject>(value);
  }

  String Inspect() override
  {
    return std::to_string(value);
  }

  DoubleObjectPtr ToDouble()
  {
    return std::make_shared<DoubleObject>(static_cast<double>(value));
  }
};

typedef std::shared_ptr<IntegerObject> IntegerObjectPtr;