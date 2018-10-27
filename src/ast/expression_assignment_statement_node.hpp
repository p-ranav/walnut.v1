#pragma once
#include <node.hpp>

namespace walnut
{

  // Example: x = [1, 2, 3, 4, 5]
  // x[0] = 2
  // Above statement is an expression assignment statement
  // left of '=' is an expression that evaluates to a reference
  // and that reference is assigned to whatever expression is
  // to the right of '='
  struct ExpressionAssignmentStatementNode : Node
  {
    NodePtr left;
    NodePtr expression;
    ExpressionAssignmentStatementNode() : Node(EXPRESSION_ASSIGNMENT_STATEMENT) {}

    String ToString() override
    {
      return left->ToString() + " = " + expression->ToString() + ";";
    }
  };

  typedef std::shared_ptr<ExpressionAssignmentStatementNode> ExpressionAssignmentStatementNodePtr;

}