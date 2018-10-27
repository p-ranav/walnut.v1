#pragma once
#include <object.hpp>
#include <memory>

namespace walnut
{

  struct BooleanObject : Object
  {
    bool value;
    explicit BooleanObject(bool value) : Object(BOOLEAN, false, true), value(value) {}

    ObjectPtr Copy() override
    {
      return std::make_shared<BooleanObject>(value);
    }

    String Inspect() override
    {
      return (value == true) ? "true" : "false";
    }
  };

  typedef std::shared_ptr<BooleanObject> BooleanObjectPtr;

}