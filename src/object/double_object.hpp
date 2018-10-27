#pragma once
#include <object.hpp>
#include <integer_object.hpp>
#include <iomanip>
#include <sstream>
#include <memory>

namespace walnut
{

  struct DoubleObject : Object
  {
    double value;
    std::streamsize str_precision;
    explicit DoubleObject(double value) : Object(DOUBLE, false, true), value(value), str_precision(2) {}

    ObjectPtr Copy() override
    {
      return std::make_shared<DoubleObject>(value);
    }

    String Inspect() override
    {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(str_precision) << value;
      return stream.str();
    }
  };

  typedef std::shared_ptr<DoubleObject> DoubleObjectPtr;

}