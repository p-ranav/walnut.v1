#pragma once
#include <node.hpp>

struct AstReturnStatementNode : AstNode
{
  AstNodePtr expression;
  AstReturnStatementNode() : 
    AstNode(RETURN_STATEMENT) {}
};

typedef std::shared_ptr<AstReturnStatementNode> AstReturnStatementNodePtr;