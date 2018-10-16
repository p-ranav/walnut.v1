#pragma once
#include <node.hpp>
#include <token.hpp>

struct CallExpressionNode : Node
{
  NodePtr function;
  std::vector<NodePtr> arguments;
  explicit CallExpressionNode() :
    Node(CALL_EXPRESSION),
    function(nullptr),
    arguments({}) {}
};

typedef std::shared_ptr<CallExpressionNode> CallExpressionNodePtr;