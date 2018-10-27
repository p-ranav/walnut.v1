#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

namespace walnut
{

  struct IfExpressionNode : Node
  {
    NodePtr condition;
    BlockStatementNodePtr consequence;
    BlockStatementNodePtr alternative;

    explicit IfExpressionNode() : Node(IF_EXPRESSION),
      condition(nullptr),
      consequence(nullptr),
      alternative(nullptr) {}

    String ToString() override
    {
      String result = "";
      result += "if (" + condition->ToString() + ") " + consequence->ToString();
      if (alternative != nullptr)
        result += " else " + alternative->ToString();
      return result;
    }
  };

  typedef std::shared_ptr<IfExpressionNode> IfExpressionNodePtr;

}