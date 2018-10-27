#pragma once
#include <node.hpp>
#include <identifier_node.hpp>

namespace walnut
{

  struct VarStatementNode : Node
  {
    IdentifierNodePtr name;
    NodePtr expression;
    VarStatementNode() : Node(VAR_STATEMENT) {}

    String ToString() override
    {
      return name->ToString() + " = " + expression->ToString() + ";";
    }
  };

  typedef std::shared_ptr<VarStatementNode> VarStatementNodePtr;

}