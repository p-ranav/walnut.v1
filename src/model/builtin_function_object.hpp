#pragma once
#include <object.hpp>
#include <memory>
#include <vector>
#include <functional>

struct BuiltinFunctionObject : Object
{
  typedef std::function<ObjectPtr(std::vector<ObjectPtr>)> BuiltinFunction;
  BuiltinFunction function;

  BuiltinFunctionObject(BuiltinFunction function) :
    Object(BUILTIN_FUNCTION), 
    function(function) {}

  String Inspect() override {
    return "";
  }
};

typedef std::shared_ptr<BuiltinFunctionObject> BuiltinFunctionObjectPtr;