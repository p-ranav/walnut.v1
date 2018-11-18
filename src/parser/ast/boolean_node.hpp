#pragma once
#include <node.hpp>
#include <token.hpp>

namespace walnut
{

struct BooleanNode : Node
{
  bool value;
  explicit BooleanNode(Token token, bool value) : Node(token, BOOLEAN),
                                                  value(value) {}

  String ToString() override
  {
    return (value == true) ? "true" : "false";
  }
};

typedef std::shared_ptr<BooleanNode> BooleanNodePtr;

} // namespace walnut