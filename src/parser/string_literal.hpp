#pragma once
#include <node_type.hpp>
#include <node.hpp>
#include <iostream>
#include <string>

namespace parser
{
  struct string_literal_node : node
  {
    std::string value;
    explicit string_literal_node(std::string value) : node(STRING_LITERAL), value(value) {}

    void print() override {
      std::cout << "\"" << value << "\"" << std::endl;
    }

  };

}