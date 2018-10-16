#pragma once
#include <node.hpp>

struct ReturnStatementNode : Node
{
  NodePtr expression;
  ReturnStatementNode() : 
    Node(RETURN_STATEMENT) {}
};

typedef std::shared_ptr<ReturnStatementNode> ReturnStatementNodePtr;