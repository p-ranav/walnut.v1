#pragma once
#include <object.hpp>
#include <memory>
#include <vector>

struct ArrayObject : Object
{
  std::vector<ObjectPtr> elements;
  explicit ArrayObject(const std::vector<ObjectPtr>& elements) : Object(ARRAY), elements(elements) {}

  String Inspect() override {
    String result = "";
    result += "[";
    if (elements.size() == 1)
    {
      result += elements[0]->Inspect();
    }
    else if (elements.size() > 1)
    {
      for (size_t i = 0; i < elements.size() - 1; i++)
      {
        result += elements[i]->Inspect() + ", ";
      }
      result += elements[elements.size() - 1]->Inspect();
    }
    result += "]";
    return result;
  }
};

typedef std::shared_ptr<ArrayObject> ArrayObjectPtr;