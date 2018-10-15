#pragma once
#include <node.hpp>
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <vector>

struct AstFunctionLiteralNode : AstNode
{
  std::vector<AstIdentifierNodePtr> parameters;
  AstBlockStatementNodePtr body;
  explicit AstFunctionLiteralNode() :
    AstNode(FUNCTION),
    parameters({}),
    body(nullptr) {}
};

typedef std::shared_ptr<AstFunctionLiteralNode> AstFunctionLiteralNodePtr;