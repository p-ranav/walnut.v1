#pragma once
#include <object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <memory>
#include <vector>

namespace walnut
{

struct ArrayObject : Object
{
  std::vector<ObjectPtr> elements;

  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  ArrayObject() : Object(ARRAY, true), elements({}), iterator(elements.begin()) {}

  explicit ArrayObject(const std::vector<ObjectPtr> &elements) : Object(ARRAY, true),
                                                                 elements(elements), iterator(this->elements.begin()) {}

  ObjectPtr Copy() override
  {
    std::shared_ptr<ArrayObject> result = std::make_shared<ArrayObject>();
    for (auto &element : elements)
      result->elements.push_back(element->Copy());
    result->iterator = result->elements.begin();
    result->iterable = true;
    return result;
  }

  void IterableInit() override
  {
    iterator = elements.begin();
  }

  ObjectIterator IterableNext() override
  {
    if (iterator != elements.end())
      iterator = iterator + 1;
    return iterator;
  }

  ObjectPtr IterableCurrentValue() override
  {
    if (iterator != elements.end())
      return *(iterator);
    else
      return std::make_shared<NullObject>();
  }

  std::vector<ObjectPtr>::iterator IterableEnd() override
  {
    return elements.end();
  }

  size_t IterableSize() override
  {
    return elements.size();
  }

  void IterableAppend(ObjectPtr value) override
  {
    elements.push_back(value);
  }

  String Inspect() override
  {
    String result = "";
    result += "[";
    if (elements.size() == 1)
    {
      if (elements[0]->type != ObjectType::STRING)
        result += elements[0]->Inspect();
      else
      {
        StringObjectPtr string_element = std::dynamic_pointer_cast<StringObject>(elements[0]);
        result += "\"" + string_element->Value() + "\"";
      }
    }
    else if (elements.size() > 1)
    {
      for (size_t i = 0; i < elements.size() - 1; i++)
      {
        if (elements[i]->type != ObjectType::STRING)
          result += elements[i]->Inspect() + ", ";
        else
        {
          StringObjectPtr string_element = std::dynamic_pointer_cast<StringObject>(elements[i]);
          result += "\"" + string_element->Value() + "\"" + ", ";
        }
      }
      if (elements[elements.size() - 1]->type != ObjectType::STRING)
        result += elements[elements.size() - 1]->Inspect();
      else
      {
        StringObjectPtr string_element = std::dynamic_pointer_cast<StringObject>(elements[elements.size() - 1]);
        result += "\"" + string_element->Value() + "\"";
      }
    }
    result += "]";
    return result;
  }
};

typedef std::shared_ptr<ArrayObject> ArrayObjectPtr;

} // namespace walnut