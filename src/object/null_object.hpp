#pragma once
#include <object.hpp>

struct NullObject : Object
{
  explicit NullObject() : Object(NULL_) {}

  String Inspect() override
  {
    return "null";
  }
};