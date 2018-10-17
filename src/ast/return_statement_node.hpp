#pragma once
#include <node.hpp>

struct ReturnStatementNode : Node
{
  NodePtr expression;
  ReturnStatementNode() : 
    Node(RETURN_STATEMENT) {}

  String ToString() override
  {
    return "return " + expression->ToString();
  }
};

typedef std::shared_ptr<ReturnStatementNode> ReturnStatementNodePtr;