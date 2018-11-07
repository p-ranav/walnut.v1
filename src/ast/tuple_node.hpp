#pragma once
#include <node.hpp>
#include <vector>

namespace walnut
{

struct TupleNode : Node
{
  std::vector<NodePtr> elements;
  TupleNode(Token token) : Node(token, TUPLE, true), elements({}) {}
  explicit TupleNode(Token token, std::vector<NodePtr> elements) : Node(token, TUPLE, true), elements(elements) {}

  String ToString() override
  {
    String result = "";
    result += "(";
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
    result += ")";
    return result;
  }
};

typedef std::shared_ptr<TupleNode> TupleNodePtr;

} // namespace walnut
