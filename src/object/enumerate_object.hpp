#pragma once
#include <object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <integer_object.hpp>
#include <tuple_object.hpp>
#include <memory>
#include <vector>
#include <set>

namespace walnut
{

  struct EnumerateObject : Object
  {
    size_t start;
    size_t current;
    ObjectPtr elements;

    EnumerateObject() : 
      Object(ENUMERATE, true), 
      elements(nullptr),
      start(0),
      current(0) {}

    explicit EnumerateObject(ObjectPtr elements, size_t start) : 
      Object(ENUMERATE, true), 
      elements(elements),
      start(start),
      current(start) {}

    ObjectPtr Copy() override
    {
      return std::make_shared<EnumerateObject>(elements->Copy(), start);
    }

    void IterableInit() override
    {
      elements->IterableInit();
    }

    ObjectIterator IterableNext() override
    {
      current += 1;
      return elements->IterableNext();
    }

    ObjectPtr IterableCurrentValue() override
    {
      TupleObjectPtr result = std::make_shared<TupleObject>();
      result->elements.push_back(std::make_shared<IntegerObject>(current));
      result->elements.push_back(elements->IterableCurrentValue());
      return result;
    }

    std::vector<ObjectPtr>::iterator IterableEnd() override
    {
      return elements->IterableEnd();
    }

    size_t IterableSize() override
    {
      return elements->IterableSize();
    }

    void IterableAppend(ObjectPtr value) override
    {
      elements->IterableAppend(value);
    }

    String Inspect() override
    {
      String result = "enumerate ";
      result += elements->Inspect();
      result += ", start = " + std::to_string(start);
      return result;
    }
  };

  typedef std::shared_ptr<EnumerateObject> EnumerateObjectPtr;

} // namespace walnut