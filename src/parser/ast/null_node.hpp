#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

struct NullNode : Node
{
  explicit NullNode(Token token) : Node(token, NULL_) {}

  String ToString() override
  {
    return "null";
  }
};

typedef std::shared_ptr<NullNode> NullNodePtr;

} // namespace walnut