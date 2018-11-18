#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

  struct PositionalParameterNode : Node
  {
    String value;
    explicit PositionalParameterNode(Token token, StringConstRef value) :
      Node(token, POSITIONAL_PARAMETER),
      value(value) {}

    String ToString() override
    {
      return value;
    }
  };

  typedef std::shared_ptr<PositionalParameterNode> PositionalParameterNodePtr;

} // namespace walnut