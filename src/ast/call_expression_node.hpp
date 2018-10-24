#pragma once
#include <node.hpp>
#include <tuple_node.hpp>
#include <token.hpp>

struct CallExpressionNode : Node
{
  NodePtr function;
  TupleNodePtr arguments;
  explicit CallExpressionNode() : Node(CALL_EXPRESSION),
                                  function(nullptr),
                                  arguments({}) {}

  String ToString() override
  {
    String result = "";
    result += function->ToString() + "(";
    if (arguments->elements.size() == 1)
    {
      result += arguments->elements[0]->ToString();
    }
    else if (arguments->elements.size() > 1)
    {
      for (size_t i = 0; i < arguments->elements.size() - 1; i++)
      {
        result += arguments->elements[i]->ToString() + ", ";
      }
      result += arguments->elements[arguments->elements.size() - 1]->ToString();
    }
    result += ")";
    return result;
  }
};

typedef std::shared_ptr<CallExpressionNode> CallExpressionNodePtr;