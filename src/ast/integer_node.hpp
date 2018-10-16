#pragma once
#include <node.hpp>

struct IntegerNode : Node
{
  int value;
  explicit IntegerNode(int value) : 
    Node(INTEGER), 
    value(value) {}
};