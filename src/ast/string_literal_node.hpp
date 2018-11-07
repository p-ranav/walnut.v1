#pragma once
#include <node.hpp>
#include <string>

namespace walnut
{

struct StringLiteralNode : Node
{
  String value;
  explicit StringLiteralNode(Token token, StringConstRef value) : Node(token, STRING_LITERAL, true),
                                                                  value(value) {}

  String ToString() override
  {
    return "\"" + value + "\"";
  }
};

typedef std::shared_ptr<StringLiteralNode> StringLiteralNodePtr;

} // namespace walnut