#pragma once
#include <node.hpp>
#include <node_type.hpp>
#include <types.hpp>
#include <token.hpp>
#include <memory>

namespace ast
{
  struct prefix_expression_node : node
  {
    lexer::token_type prefix_operator;
    std::shared_ptr<node> right;

    explicit prefix_expression_node(lexer::token_type prefix_operator) :
      node(PREFIX_EXPRESSION),
      prefix_operator(prefix_operator),
      right(nullptr)
    {}

    void print() override {
      std::cout << "(";
      std::cout << prefix_operator;
      right->print();
      std::cout << ")";
    }

  };
}