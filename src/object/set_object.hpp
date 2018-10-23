#pragma once
#include <object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <memory>
#include <vector>
#include <set>

struct SetObject : Object
{
  std::vector<ObjectPtr> elements;

  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  SetObject() : Object(SET, true), elements({}), iterator(elements.begin()) {}

  explicit SetObject(const std::vector<ObjectPtr> &elements) : Object(SET, true)
  {
    std::set<String> string_set;
    for (auto &element : elements)
    {
      if (string_set.find(element->Inspect()) == string_set.end())
        this->elements.push_back(element);
      string_set.insert(element->Inspect());
    }
  }

  ObjectPtr Copy() override
  {
    std::shared_ptr<SetObject> result = std::make_shared<SetObject>();
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
    std::set<String> string_set;
    for (auto &element : elements)
      string_set.insert(element->Inspect());

    if (string_set.find(value->Inspect()) == string_set.end())
      elements.push_back(value);
  }

  String Inspect() override
  {
    String result = "";
    result += "{";
    if (elements.size() == 1)
    {
      result += elements[0]->Inspect();
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
    result += "}";
    return result;
  }
};

typedef std::shared_ptr<SetObject> SetObjectPtr;