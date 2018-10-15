#pragma once
#include <node.hpp>
#include <node_type.hpp>
#include <types.hpp>
#include <memory>

namespace ast
{
  struct var_statement_node : node
  {
    std::shared_ptr<identifier_node> name;
    std::shared_ptr<node> expression;
    var_statement_node() : node(VARIABLE_DECLARATION) {}

    void print() override {
      std::cout << "var ";
      name->print();
      std::cout << " = ";
      expression->print();
    }
  };

  struct return_statement_node : node
  {
    std::shared_ptr<node> expression;
    return_statement_node() : node(RETURN_STATEMENT) {}

    void print() override {
      std::cout << "return ";
      expression->print();
    }
  };
}