#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

struct WhileExpressionNode : Node
{
  NodePtr condition;
  BlockStatementNodePtr consequence;

  explicit WhileExpressionNode() :
    Node(WHILE_EXPRESSION),
    condition(nullptr),
    consequence(nullptr) {}
};

typedef std::shared_ptr<WhileExpressionNode> WhileExpressionNodePtr;