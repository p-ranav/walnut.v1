#pragma once
#include <node.hpp>

struct AstIntegerNode : AstNode
{
  int value;
  explicit AstIntegerNode(int value) : AstNode(INTEGER), value(value) {}
};