#pragma once
#include <node_type.hpp>
#include <node.hpp>
#include <iostream>

namespace parser
{
  struct integer_node : node
  {
    int value;
    explicit integer_node(int value) : node(INTEGER), value(value) {}

    void print() override {
      std::cout << value << std::endl;
    }

  };

}