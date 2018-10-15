#pragma once
#include <node.hpp>
#include <identifier_node.hpp>

struct AstVarStatementNode : AstNode
{
  AstIdentifierNodePtr name;
  AstNodePtr expression;
  AstVarStatementNode() : 
    AstNode(VAR_STATEMENT) {}
};

typedef std::shared_ptr<AstVarStatementNode> AstVarStatementNodePtr;