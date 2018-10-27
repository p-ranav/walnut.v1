#pragma once
#include <object.hpp>
#include <memory>

namespace walnut
{

  struct CharacterObject : Object
  {
    String value;

    explicit CharacterObject(StringConstRef value) : Object(CHARACTER), value(value) {}

    ObjectPtr Copy() override
    {
      return std::make_shared<CharacterObject>(value);
    }

    String Value()
    {
      return value;
    }

    String Inspect() override
    {
      return "'" + value + "'";
    }
  };

  typedef std::shared_ptr<CharacterObject> CharacterObjectPtr;

}