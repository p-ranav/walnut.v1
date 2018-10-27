#pragma once
#include <node.hpp>
#include <token.hpp>
#include <cstdint>

namespace walnut
{

  struct IntegerNode : Node
  {
    int64_t value;
    explicit IntegerNode(Token token, int64_t value) : Node(token, INTEGER),
      value(value) {}

    String ToString() override
    {
      return std::to_string(value);
    }
  };

  typedef std::shared_ptr<IntegerNode> IntegerNodePtr;

}