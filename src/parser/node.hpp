#pragma once
#include <node_type.hpp>

namespace parser
{
  struct node
  {
    node_type type;
    explicit node(node_type type) : type(type) {}
    virtual void print() = 0;
  };
}