#pragma once
#include <node.hpp>
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <vector>

struct FunctionLiteralNode : Node
{
  std::vector<IdentifierNodePtr> parameters;
  BlockStatementNodePtr body;
  explicit FunctionLiteralNode() :
    Node(FUNCTION),
    parameters({}),
    body(nullptr) {}
};

typedef std::shared_ptr<FunctionLiteralNode> FunctionLiteralNodePtr;