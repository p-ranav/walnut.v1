#pragma once
#include <node.hpp>
#include <vector>
#include <memory>

struct AstBlockStatementNode : AstNode
{
  std::vector<AstNodePtr> statements;
  AstBlockStatementNode() : 
    AstNode(BLOCK_STATEMENT), 
    statements({}) {}
};

typedef std::shared_ptr<AstBlockStatementNode> AstBlockStatementNodePtr;