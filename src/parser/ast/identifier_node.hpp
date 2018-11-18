#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

struct IdentifierNode : Node
{
  String value;
  explicit IdentifierNode(Token token, StringConstRef value) : Node(token, IDENTIFIER),
                                                               value(value) {}

  String ToString() override
  {
    return value;
  }
};

typedef std::shared_ptr<IdentifierNode> IdentifierNodePtr;

} // namespace walnut