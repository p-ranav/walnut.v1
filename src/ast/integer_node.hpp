#pragma once
#include <node.hpp>
#include <cstdint>

struct IntegerNode : Node
{
  int64_t value;
  explicit IntegerNode(int64_t value) : Node(INTEGER),
                                    value(value) {}

  String ToString() override
  {
    return std::to_string(value);
  }
};

typedef std::shared_ptr<IntegerNode> IntegerNodePtr;