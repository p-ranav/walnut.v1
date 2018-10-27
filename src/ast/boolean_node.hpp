#pragma once
#include <node.hpp>

namespace walnut
{

  struct BooleanNode : Node
  {
    bool value;
    explicit BooleanNode(bool value) : Node(BOOLEAN),
      value(value) {}

    String ToString() override
    {
      return (value == true) ? "true" : "false";
    }
  };

  typedef std::shared_ptr<BooleanNode> BooleanNodePtr;

}