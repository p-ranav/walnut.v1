#pragma once
#include <node.hpp>
#include <string>

struct AstStringNode : AstNode
{
  String value;
  explicit AstStringNode(StringConstRef value) : 
    AstNode(STRING_LITERAL), 
    value(value) {}
};