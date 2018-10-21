#pragma once
#include <node.hpp>
#include <string>

struct CharacterNode : Node
{
  String value;
  explicit CharacterNode(StringConstRef value) :
    Node(CHARACTER),
    value(value) {}

  String ToString() override
  {
    return "'" + value + "'";
  }
};

typedef std::shared_ptr<CharacterNode> CharacterNodePtr;