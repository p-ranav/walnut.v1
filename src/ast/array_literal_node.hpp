#pragma once
#include <node.hpp>
#include <vector>

struct ArrayLiteralNode : Node
{
  std::vector<NodePtr> elements;
  explicit ArrayLiteralNode() :
    Node(ARRAY_LITERAL),
    elements({}) {}
};

typedef std::shared_ptr<ArrayLiteralNode> ArrayLiteralNodePtr;
