#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

  struct TypeNode : Node
  {
    Token::Type value;
    explicit TypeNode(Token token, Token::Type value) : Node(token, TYPE),
      value(value) {}

    String ToString() override
    {
      return TokenString(value);
    }
  };

  typedef std::shared_ptr<TypeNode> TypeNodePtr;

}