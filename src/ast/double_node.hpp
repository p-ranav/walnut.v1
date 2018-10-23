#pragma once
#include <node.hpp>

struct DoubleNode : Node
{
  double value;
  explicit DoubleNode(double value) : Node(DOUBLE),
                                      value(value) {}

  String ToString() override
  {
    return std::to_string(value);
  }
};

typedef std::shared_ptr<DoubleNode> DoubleNodePtr;