#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

  struct PositionalArgumentNode : Node
  {
    String value;
    explicit PositionalArgumentNode(Token token, StringConstRef value) : 
      Node(token, POSITIONAL_ARGUMENT),
      value(value) {}

    String ToString() override
    {
      return value;
    }
  };

  typedef std::shared_ptr<PositionalArgumentNode> PositionalArgumentNodePtr;

} // namespace walnut