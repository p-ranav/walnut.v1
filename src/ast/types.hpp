#pragma once
#include <node_type.hpp>
#include <node.hpp>
#include <iostream>
#include <string>

namespace ast
{
  struct boolean_node : node
  {
    bool value;
    explicit boolean_node(bool value) : node(BOOLEAN), value(value) {}

    void print() override {
      std::cout << (value ? "true" : "false") << std::endl;
    }
  };

  struct integer_node : node
  {
    int value;
    explicit integer_node(int value) : node(INTEGER), value(value) {}

    void print() override {
      std::cout << value << std::endl;
    }
  };

  struct double_node : node
  {
    double value;
    explicit double_node(double value) : node(DOUBLE), value(value) {}

    void print() override {
      std::cout << value << std::endl;
    }
  };

  struct string_literal_node : node
  {
    std::string value;
    explicit string_literal_node(std::string value) : node(STRING_LITERAL), value(value) {}

    void print() override {
      std::cout << "\"" << value << "\"" << std::endl;
    }
  };

  struct identifier_node : node
  {
    std::string value;
    explicit identifier_node(std::string value) : node(IDENTIFIER), value(value) {}

    void print() override {
      std::cout << value << std::endl;
    }
  };
}