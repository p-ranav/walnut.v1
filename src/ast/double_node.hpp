#pragma once
#include <node.hpp>

struct AstDoubleNode : AstNode
{
  double value;
  explicit AstDoubleNode(double value) : AstNode(DOUBLE), value(value) {}
};