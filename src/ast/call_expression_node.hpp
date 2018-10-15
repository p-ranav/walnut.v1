#pragma once
#include <node.hpp>
#include <token.hpp>

struct AstCallExpressionNode : AstNode
{
  AstNodePtr function;
  std::vector<AstNodePtr> arguments;
  explicit AstCallExpressionNode() :
    AstNode(CALL_EXPRESSION),
    function(nullptr),
    arguments({}) {}
};

typedef std::shared_ptr<AstCallExpressionNode> AstCallExpressionNodePtr;