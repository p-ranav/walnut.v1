#pragma once
#include <object.hpp>
#include <integer_object.hpp>
#include <double_object.hpp>
#include <null_object.hpp>

struct RangeObject : Object
{
  double start;
  double end;
  double step;
  double current;
  bool integral_range;
  std::vector<ObjectPtr> elements;

  typedef std::vector<ObjectPtr>::iterator ObjectIterator;
  ObjectIterator iterator;

  explicit RangeObject(double start, double end, double step, bool integral_range) :
    Object(RANGE, true),
    start(start),
    end(end),
    step(step),
    current(start),
    integral_range(integral_range) {}

  void IterableInit() override
  {
    if (elements.size() > 0)
      elements.clear();

    if (integral_range)
      elements.push_back(std::make_shared<IntegerObject>(static_cast<int>(start)));
    else
      elements.push_back(std::make_shared<DoubleObject>(start));
  }

  ObjectIterator IterableNext() override
  {
    current = current + step;
    if (start < end && current >= end) {
        return elements.end();
    }
    else if (start > end && current <= end) {
      return elements.end();
    }

    if (elements.size() == 0)
    {
      if (integral_range)
        elements.push_back(std::make_shared<IntegerObject>(static_cast<int>(current)));
      else
        elements.push_back(std::make_shared<DoubleObject>(current));
    }
    else
    {
      if (integral_range)
        elements[0] = std::make_shared<IntegerObject>(static_cast<int>(current));
      else
        elements[0] = std::make_shared<DoubleObject>(current);
    }

    return elements.begin();
  }

  ObjectPtr IterableCurrentValue() override
  {
    if (elements.size() == 0)
      return std::make_shared<NullObject>();
    else
      return elements[0];
  }

  std::vector<ObjectPtr>::iterator IterableEnd() override
  {
    return elements.end();
  }

  void IterableAppend(ObjectPtr value) override {}

  size_t IterableSize() override
  {
    return elements.size();
  }

  ObjectPtr Copy() override
  {
    std::shared_ptr<RangeObject> result = std::make_shared<RangeObject>(start, end, step, integral_range);
    result->current = current;
    for (auto& element : elements)
      result->elements.push_back(element);
    return result;
  }

  String Inspect() override {
    return "range [" + std::to_string(start) + ", " + std::to_string(end) + ") @ " + std::to_string(step);
  }
};