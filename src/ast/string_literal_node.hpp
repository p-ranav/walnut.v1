#pragma once
#include <node.hpp>
#include <string>

struct StringLiteralNode : Node
{
  String value;
  explicit StringLiteralNode(StringConstRef value) :
    Node(STRING_LITERAL), 
    value(value) {}

  String ToString() override
  {
    return "\"" + value + "\"";
  }
};

typedef std::shared_ptr<StringLiteralNode> StringLiteralNodePtr;