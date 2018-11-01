#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

  struct PrefixExpressionNode : Node
  {
    Token::Type prefix_operator;
    NodePtr right;

    explicit PrefixExpressionNode(Token token, Token::Type prefix_operator) : Node(token, PREFIX_EXPRESSION),
      prefix_operator(prefix_operator),
      right(nullptr) {}

    String ToString() override
    {
      return "(" + TokenString(prefix_operator) + right->ToString() + ")";
    }
  };

  typedef std::shared_ptr<PrefixExpressionNode> PrefixExpressionNodePtr;

}