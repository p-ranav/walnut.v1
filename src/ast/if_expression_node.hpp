#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

struct IfExpressionNode : Node
{
  NodePtr condition;
  BlockStatementNodePtr consequence;
  BlockStatementNodePtr alternative;

  explicit IfExpressionNode() : 
    Node(IF_EXPRESSION), 
    condition(nullptr), 
    consequence(nullptr), 
    alternative(nullptr) {}
};

typedef std::shared_ptr<IfExpressionNode> IfExpressionNodePtr;