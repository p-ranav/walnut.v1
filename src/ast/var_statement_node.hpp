#pragma once
#include <node.hpp>
#include <identifier_node.hpp>

namespace walnut
{

  struct VarStatementNode : Node
  {
    IdentifierNodePtr name;
    NodePtr expression;
    VarStatementNode(Token token) : Node(token, VAR_STATEMENT) {}

    String ToString() override
    {
      return name->ToString() + " = " + expression->ToString() + ";";
    }
  };

  typedef std::shared_ptr<VarStatementNode> VarStatementNodePtr;

}