#pragma once
#include <object.hpp>
#include <memory>

struct ReturnObject : Object
{
  ObjectPtr value;
  explicit ReturnObject(ObjectPtr value) : Object(RETURN), value(value) {}

  String Inspect() override {
    return value->Inspect();
  }
};

typedef std::shared_ptr<ReturnObject> ReturnObjectPtr;