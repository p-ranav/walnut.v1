#pragma once
#include <object.hpp>

struct DoubleObject : Object
{
  double value;
  explicit DoubleObject(double value) : Object(DOUBLE), value(value) {}

  String Inspect() override {
    return std::to_string(value);
  }
};

typedef std::shared_ptr<DoubleObject> DoubleObjectPtr;