#pragma once
#include <node.hpp>

struct BooleanNode : Node
{
  bool value;
  explicit BooleanNode(bool value) : 
    Node(BOOLEAN), 
    value(value) {}
};