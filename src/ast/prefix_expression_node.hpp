#pragma once
#include <node.hpp>
#include <token.hpp>

struct PrefixExpressionNode : Node
{
  TokenType prefix_operator;
  NodePtr right;

  explicit PrefixExpressionNode(TokenType prefix_operator) : 
    Node(PREFIX_EXPRESSION), 
    prefix_operator(prefix_operator), 
    right(nullptr) {}
};

typedef std::shared_ptr<PrefixExpressionNode> PrefixExpressionNodePtr;