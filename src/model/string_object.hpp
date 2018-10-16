#pragma once
#include <object.hpp>
#include <memory>

struct StringObject : Object
{
  String value;
  explicit StringObject(String value) : Object(STRING), value(value) {}

  String Inspect() override {
    return "\"" + value + "\"";
  }
};

typedef std::shared_ptr<StringObject> StringObjectPtr;