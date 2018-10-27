#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

namespace walnut
{

  struct WhileExpressionNode : Node
  {
    NodePtr condition;
    BlockStatementNodePtr consequence;

    explicit WhileExpressionNode() : Node(WHILE_EXPRESSION),
      condition(nullptr),
      consequence(nullptr) {}

    String ToString() override
    {
      return "while (" + condition->ToString() + ") " + consequence->ToString();
    }
  };

  typedef std::shared_ptr<WhileExpressionNode> WhileExpressionNodePtr;

}