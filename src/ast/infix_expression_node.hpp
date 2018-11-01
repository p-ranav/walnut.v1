#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

  struct InfixExpressionNode : Node
  {
    NodePtr left;
    Token::Type infix_operator;
    NodePtr right;

    explicit InfixExpressionNode(Token token, Token::Type infix_operator) : Node(token, INFIX_EXPRESSION),
      left(nullptr),
      infix_operator(infix_operator),
      right(nullptr) {}

    String ToString() override
    {
      return "(" + left->ToString() + " " + TokenString(infix_operator) + " " + right->ToString() + ")";
    }
  };

  typedef std::shared_ptr<InfixExpressionNode> InfixExpressionNodePtr;

}