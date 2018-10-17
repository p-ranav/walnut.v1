#pragma once
#include <object.hpp>
#include <memory>
#include <vector>

struct ArrayObject : Object
{
  std::vector<ObjectPtr> elements;
  explicit ArrayObject(const std::vector<ObjectPtr>& elements) : Object(ARRAY), elements(elements) {}

  String Inspect() override {
    return "list";
  }
};

typedef std::shared_ptr<ArrayObject> ArrayObjectPtr;