#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

  struct InExpressionNode : Node
  {
    NodePtr iterator;
    NodePtr iterable;
    explicit InExpressionNode(Token token) : Node(token, IN_EXPRESSION) {}

    String ToString() override
    {
      return iterator->ToString() + " in " + iterable->ToString();
    }
  };

  typedef std::shared_ptr<InExpressionNode> InExpressionNodePtr;

}