#pragma once
#include <node.hpp>

struct DoubleNode : Node
{
  double value;
  explicit DoubleNode(double value) : 
    Node(DOUBLE), 
    value(value) {}
};

typedef std::shared_ptr<DoubleNode> DoubleNodePtr;