#pragma once
#include <node.hpp>
#include <token.hpp>
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <vector>

namespace walnut
{

struct FunctionLiteralNode : Node
{
  std::vector<NodePtr> parameters;
  BlockStatementNodePtr body;
  bool variadic_positional_arguments_expected;
  bool variadic_keyword_arguments_expected;

  explicit FunctionLiteralNode(Token token) : Node(token, FUNCTION),
                                              parameters({}),
                                              variadic_positional_arguments_expected(false),
                                              variadic_keyword_arguments_expected(false),
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

} // namespace walnut