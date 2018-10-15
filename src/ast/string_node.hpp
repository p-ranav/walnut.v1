#pragma once
#include <node.hpp>
#include <string>

typedef std::string String;
typedef const std::string &StringConstRef;

struct AstStringNode : AstNode
{
  String value;
  explicit AstStringNode(StringConstRef value) : 
    AstNode(STRING_LITERAL), 
    value(value) {}
};