#pragma once
#include <node_type.hpp>
#include <node.hpp>
#include <iostream>

namespace parser
{
  struct double_node : node
  {
    double value;
    explicit double_node(double value) : node(DOUBLE), value(value) {}

    void print() override {
      std::cout << value << std::endl;
    }

  };

}