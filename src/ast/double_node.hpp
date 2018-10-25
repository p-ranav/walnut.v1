#pragma once
#include <node.hpp>
#include <string>
#include <iomanip> // setprecision
#include <sstream> // stringstream

struct DoubleNode : Node
{
  double value;
  explicit DoubleNode(double value) : Node(DOUBLE),
                                      value(value) {}

  String ToString() override
  {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    return stream.str();
  }
};

typedef std::shared_ptr<DoubleNode> DoubleNodePtr;