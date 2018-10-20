#pragma once
#include <object.hpp>
#include <memory>
#include <vector>

struct ArrayObject : Object
{
  std::vector<ObjectPtr> elements;

  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  ArrayObject() : Object(ARRAY, true), elements({}), iterator(elements.begin()) {}

  explicit ArrayObject(const std::vector<ObjectPtr>& elements) : Object(ARRAY, true), 
    elements(elements), iterator(this->elements.begin()) {}

  ObjectIterator IterableBegin() override
  {
    return iterator;
  }

  ObjectIterator IterableNext() override
  {
    return iterator++;
  }

  ObjectPtr IterableCurrentValue() override
  {
    if (iterator != elements.end())
      return *(iterator);
    else
      return nullptr;
  }

  std::vector<ObjectPtr>::iterator IterableEnd() override
  {
    return elements.end() - 1;
  }

  size_t IterableSize() override
  {
    return elements.size();
  }

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