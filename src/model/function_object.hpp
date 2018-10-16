#pragma once
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <object.hpp>
#include <environment.hpp>

struct FunctionObject : Object
{
  std::vector<IdentifierNodePtr> parameters;
  BlockStatementNodePtr body;
  EnvironmentPtr environment;
  explicit FunctionObject(const std::vector<IdentifierNodePtr>& parameters, 
    BlockStatementNodePtr body, EnvironmentPtr environment) : 
    Object(FUNCTION),
    parameters(parameters),
    body(body),
    environment(environment) {}

  String Inspect() override {
    String buffer;
    buffer += "function(";
    for (size_t i = 0; i < parameters.size() - 1; i++)
    {
      buffer += parameters[i]->value;
      buffer += ", ";
    }
    if (parameters.size() > 0)
      buffer += parameters[parameters.size() - 1]->value;

    buffer += ")";
    // TODO: print body
    return buffer;
  }
};

typedef std::shared_ptr<FunctionObject> FunctionObjectPtr;