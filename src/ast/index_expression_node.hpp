#pragma once
#include <node.hpp>
#include <token.hpp>
#include <vector>

namespace walnut
{

  struct IndexExpressionNode : Node
  {
    NodePtr left;
    NodePtr index;
    explicit IndexExpressionNode(Token token, NodePtr left) : Node(token, INDEX_EXPRESSION),
      left(left),
      index(nullptr) {}

    String ToString() override
    {
      return left->ToString() + "[" + index->ToString() + "]";
    }
  };

  typedef std::shared_ptr<IndexExpressionNode> IndexExpressionNodePtr;

}
