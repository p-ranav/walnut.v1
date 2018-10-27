#pragma once
#include <node.hpp>
#include <string>

namespace walnut
{

  struct IdentifierNode : Node
  {
    String value;
    explicit IdentifierNode(StringConstRef value) : Node(IDENTIFIER),
      value(value) {}

    String ToString() override
    {
      return value;
    }
  };

  typedef std::shared_ptr<IdentifierNode> IdentifierNodePtr;

}