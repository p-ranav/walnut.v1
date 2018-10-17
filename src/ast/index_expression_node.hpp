#pragma once
#include <node.hpp>
#include <vector>

struct IndexExpressionNode : Node
{
  NodePtr left;
  NodePtr index;
  explicit IndexExpressionNode(NodePtr left) :
    Node(INDEX_EXPRESSION),
    left(left),
    index(nullptr){}

  String ToString() override
  {
    return left->ToString() + "[" + index->ToString() + "]";
  }

};

typedef std::shared_ptr<IndexExpressionNode> IndexExpressionNodePtr;
