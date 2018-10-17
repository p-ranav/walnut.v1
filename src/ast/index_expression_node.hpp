#pragma once
#include <node.hpp>
#include <vector>

struct IndexExpressionNode : Node
{
  NodePtr left;
  NodePtr index;
  explicit IndexExpressionNode() :
    Node(INDEX_EXPRESSION),
    left(nullptr),
    index(nullptr){}
};

typedef std::shared_ptr<IndexExpressionNode> IndexExpressionNodePtr;
