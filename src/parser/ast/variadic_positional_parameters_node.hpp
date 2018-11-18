#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

  struct VariadicPositionalParameterNode : Node
  {
    String value;
    explicit VariadicPositionalParameterNode(Token token, StringConstRef value) :
      Node(token, VARIADIC_POSITIONAL_PARAMETER),
      value(value) {}

    String ToString() override
    {
      return "*" + value;
    }
  };

  typedef std::shared_ptr<VariadicPositionalParameterNode> VariadicPositionalParameterNodePtr;

} // namespace walnut