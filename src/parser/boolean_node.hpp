#pragma once
#include <node_type.hpp>
#include <node.hpp>
#include <iostream>

namespace parser
{
  struct boolean_node : node
  {
    bool value;
    explicit boolean_node(bool value) : node(BOOLEAN), value(value) {}

    void print() override {
      std::cout << (value ? "true" : "false") << std::endl;
    }

  };

}