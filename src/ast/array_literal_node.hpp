#pragma once
#include <node.hpp>
#include <vector>

struct ArrayLiteralNode : Node
{
  std::vector<NodePtr> elements;
  explicit ArrayLiteralNode() :
    Node(ARRAY_LITERAL, true),
    elements({}) {}

  String ToString() override
  {
    String result = "";
    result += "[";
    if (elements.size() == 1)
    {
      result += elements[0]->ToString();
    }
    else if (elements.size() > 1)
    {
      for (size_t i = 0; i < elements.size() - 1; i++)
      {
        result += elements[i]->ToString() + ", ";
      }
      result += elements[elements.size() - 1]->ToString();
    }
    result += "]";
    return result;
  }
};

typedef std::shared_ptr<ArrayLiteralNode> ArrayLiteralNodePtr;
