#pragma once
#include <node.hpp>
#include <block_statement_node.hpp>
#include <memory>

struct AstIfExpressionNode : AstNode
{
  AstNodePtr condition;
  AstBlockStatementNodePtr consequence;
  AstBlockStatementNodePtr alternative;

  explicit AstIfExpressionNode() : 
    AstNode(IF_EXPRESSION), 
    condition(nullptr), 
    consequence(nullptr), 
    alternative(nullptr) {}
};

typedef std::shared_ptr<AstIfExpressionNode> AstIfExpressionNodePtr;