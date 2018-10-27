#pragma once
#include <node.hpp>
#include <string>

namespace walnut
{

  struct StringLiteralNode : Node
  {
    String value;
    explicit StringLiteralNode(StringConstRef value) : Node(STRING_LITERAL, true),
      value(value) {}

    String ToString() override
    {
      return "\"" + value + "\"";
    }
  };

  typedef std::shared_ptr<StringLiteralNode> StringLiteralNodePtr;

}