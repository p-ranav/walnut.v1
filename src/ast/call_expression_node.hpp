#pragma once
#include <node.hpp>
#include <token.hpp>

struct CallExpressionNode : Node
{
  NodePtr function;
  std::vector<NodePtr> arguments;
  explicit CallExpressionNode() : Node(CALL_EXPRESSION),
                                  function(nullptr),
                                  arguments({}) {}

  String ToString() override
  {
    String result = "";
    result += function->ToString() + "(";
    if (arguments.size() == 1)
    {
      result += arguments[0]->ToString();
    }
    else if (arguments.size() > 1)
    {
      for (size_t i = 0; i < arguments.size() - 1; i++)
      {
        result += arguments[i]->ToString() + ", ";
      }
      result += arguments[arguments.size() - 1]->ToString();
    }
    result += ")";
    return result;
  }
};

typedef std::shared_ptr<CallExpressionNode> CallExpressionNodePtr;