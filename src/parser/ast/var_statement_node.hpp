#pragma once
#include <node.hpp>
#include <identifier_node.hpp>

namespace walnut
{

struct VarStatementNode : Node
{
  IdentifierNodePtr name;
  NodePtr expression;

  enum StatementType
  {
    INITIALIZATION,
    ASSIGNMENT
  };
  enum StatementType statement_type;

  VarStatementNode(Token token) : Node(token, VAR_STATEMENT) {}

  String ToString() override
  {
    return name->ToString() + " = " + expression->ToString() + ";";
  }
};

typedef std::shared_ptr<VarStatementNode> VarStatementNodePtr;

} // namespace walnut