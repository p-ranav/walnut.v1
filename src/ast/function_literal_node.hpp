#pragma once
#include <node.hpp>
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <vector>

namespace walnut
{

  struct FunctionLiteralNode : Node
  {
    std::vector<IdentifierNodePtr> parameters;
    BlockStatementNodePtr body;
    explicit FunctionLiteralNode() : Node(FUNCTION),
      parameters({}),
      body(nullptr) {}

    String ToString() override
    {
      String result = "";
      result += "function(";
      if (parameters.size() == 1)
      {
        result += parameters[0]->ToString();
      }
      else if (parameters.size() > 1)
      {
        for (size_t i = 0; i < parameters.size() - 1; i++)
        {
          result += parameters[i]->ToString() + ", ";
        }
        result += parameters[parameters.size() - 1]->ToString();
      }
      result += ") " + body->ToString();
      return result;
    }
  };

  typedef std::shared_ptr<FunctionLiteralNode> FunctionLiteralNodePtr;

}