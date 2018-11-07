#pragma once
#include <node.hpp>
#include <token.hpp>
#include <block_statement_node.hpp>
#include <memory>

namespace walnut
{

  struct IfExpressionNode : Node
  {
    std::vector<NodePtr> conditions;
    std::vector<BlockStatementNodePtr> consequences;
    BlockStatementNodePtr alternative; // else case

    explicit IfExpressionNode(Token token) : Node(token, IF_EXPRESSION),
      conditions({}),
      consequences({}),
      alternative(nullptr) {}

    String ToString() override
    {
      String result = "";
      for (size_t i = 0; i < conditions.size(); i++)
      {
        if (i > 0)
          result += " else ";
        result += "if " + conditions[i]->ToString() + " " + consequences[i]->ToString();
      }
      if (alternative != nullptr)
        result += " else " + alternative->ToString();
      return result;
    }
  };

  typedef std::shared_ptr<IfExpressionNode> IfExpressionNodePtr;

}