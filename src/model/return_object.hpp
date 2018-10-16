#pragma once
#include <object.hpp>

struct ReturnObject : Object
{
  ObjectPtr value;
  explicit ReturnObject() : Object(RETURN) {}

  String Inspect() override {
    return value->Inspect();
  }
};