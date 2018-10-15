#pragma once
#include <node.hpp>
#include <token.hpp>

struct AstInfixExpressionNode : AstNode
{
  AstNodePtr left;
  TokenType infix_operator;
  AstNodePtr right;

  explicit AstInfixExpressionNode(TokenType infix_operator) : 
    AstNode(INFIX_EXPRESSION),
    left(nullptr),
    infix_operator(infix_operator),
    right(nullptr) {}
};

typedef std::shared_ptr<AstInfixExpressionNode> AstInfixExpressionNodePtr;