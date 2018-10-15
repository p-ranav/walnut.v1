#pragma once
#include <node.hpp>

struct AstBooleanNode : AstNode
{
  bool value;
  explicit AstBooleanNode(bool value) : AstNode(BOOLEAN), value(value) {}
};