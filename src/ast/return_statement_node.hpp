#pragma once
#include <node.hpp>

namespace walnut
{

  struct ReturnStatementNode : Node
  {
    NodePtr expression;
    ReturnStatementNode(Token token) : Node(token, RETURN_STATEMENT) {}

    String ToString() override
    {
      return "return " + expression->ToString();
    }
  };

  typedef std::shared_ptr<ReturnStatementNode> ReturnStatementNodePtr;

}