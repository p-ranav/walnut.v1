#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

struct ForExpressionNode : Node
{
  std::vector<NodePtr> initialization;
  std::vector<NodePtr> condition;
  std::vector<NodePtr> increment;
  BlockStatementNodePtr statements;

  explicit ForExpressionNode() :
    Node(FOR_EXPRESSION),
    initialization({}),
    condition({}),
    increment({}),
    statements(nullptr) {}
};

typedef std::shared_ptr<ForExpressionNode> ForExpressionNodePtr;