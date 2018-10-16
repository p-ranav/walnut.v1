#pragma once
#include <node.hpp>
#include <token.hpp>

struct InfixExpressionNode : Node
{
  NodePtr left;
  TokenType infix_operator;
  NodePtr right;

  explicit InfixExpressionNode(TokenType infix_operator) : 
    Node(INFIX_EXPRESSION),
    left(nullptr),
    infix_operator(infix_operator),
    right(nullptr) {}
};

typedef std::shared_ptr<InfixExpressionNode> InfixExpressionNodePtr;