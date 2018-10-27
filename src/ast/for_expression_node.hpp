#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>
#include <vector>

namespace walnut
{

  struct ForExpressionNode : Node
  {
    std::vector<NodePtr> iterators;
    NodePtr iterable;
    BlockStatementNodePtr body;

    explicit ForExpressionNode() : Node(FOR_EXPRESSION),
      iterators({}),
      iterable(nullptr),
      body(nullptr) {}

    String ToString() override
    {
      return "for ...";
    }
  };

  typedef std::shared_ptr<ForExpressionNode> ForExpressionNodePtr;

}