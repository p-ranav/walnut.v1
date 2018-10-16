#pragma once
#include <object.hpp>

struct StringObject : Object
{
  String value;
  explicit StringObject(String value) : Object(STRING), value(value) {}

  String Inspect() override {
    return "\"" + value + "\"";
  }
};