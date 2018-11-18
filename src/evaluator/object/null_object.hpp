#pragma once
#include <object.hpp>

namespace walnut
{

struct NullObject : Object
{
  explicit NullObject() : Object(NULL_) {}

  String Inspect() override
  {
    return "null";
  }
};

} // namespace walnut