#pragma once
#include <object.hpp>
#include <memory>

struct CharacterObject : Object
{
  String value;

  explicit CharacterObject(StringConstRef value) : Object(CHARACTER), value(value) {}

  String Inspect() override {
    return "'" + value + "'";
  }
};

typedef std::shared_ptr<CharacterObject> CharacterObjectPtr;