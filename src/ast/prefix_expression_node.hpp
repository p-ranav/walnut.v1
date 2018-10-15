#pragma once
#include <node.hpp>
#include <token.hpp>

struct AstPrefixExpressionNode : AstNode
{
  TokenType prefix_operator;
  AstNodePtr right;

  explicit AstPrefixExpressionNode(TokenType prefix_operator) :
    AstNode(PREFIX_EXPRESSION),
    prefix_operator(prefix_operator),
    right(nullptr) {}
};

typedef std::shared_ptr<AstPrefixExpressionNode> AstPrefixExpressionNodePtr;