#pragma once
#include <node.hpp>
#include <identifier_node.hpp>

struct VarStatementNode : Node
{
  IdentifierNodePtr name;
  NodePtr expression;
  VarStatementNode() : 
    Node(VAR_STATEMENT) {}
};

typedef std::shared_ptr<VarStatementNode> VarStatementNodePtr;