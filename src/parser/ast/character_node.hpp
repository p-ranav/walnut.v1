#pragma once
#include <node.hpp>
#include <token.hpp>
#include <string>

namespace walnut
{

struct CharacterNode : Node
{
  String value;
  explicit CharacterNode(Token token, StringConstRef value) : Node(token, CHARACTER),
                                                              value(value) {}

  String ToString() override
  {
    return "'" + value + "'";
  }
};

typedef std::shared_ptr<CharacterNode> CharacterNodePtr;

} // namespace walnut