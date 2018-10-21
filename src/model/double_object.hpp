#pragma once
#include <object.hpp>
#include <integer_object.hpp>
#include <iomanip> // setprecision
#include <sstream> // stringstream

struct DoubleObject : Object
{
  double value;
  std::streamsize str_precision;
  explicit DoubleObject(double value) : Object(DOUBLE), value(value), str_precision(2) {}

  ObjectPtr Copy() override
  {
    return std::make_shared<DoubleObject>(value);
  }

  String Inspect() override {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(str_precision) << value;
    return stream.str();
  }

};

typedef std::shared_ptr<DoubleObject> DoubleObjectPtr;