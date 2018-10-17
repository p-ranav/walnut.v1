#pragma once
#include <identifier_node.hpp>
#include <block_statement_node.hpp>
#include <object.hpp>
#include <environment.hpp>
#include <iostream>

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

  virtual ~FunctionObject() {
    environment.reset();
  }

  String Inspect() override {
    String result = "";
    result += "function(";
    if (parameters.size() == 1)
    {
      result += parameters[0]->ToString();
    }
    else if (parameters.size() > 1)
    {
      for (size_t i = 0; i < parameters.size() - 1; i++)
      {
        result += parameters[i]->ToString() + ", ";
      }
      result += parameters[parameters.size() - 1]->ToString();
    }
    result += ") " + body->ToString();
    return result;
  }
};

typedef std::shared_ptr<FunctionObject> FunctionObjectPtr;