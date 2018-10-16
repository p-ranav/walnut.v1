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
    return "";
  }
};

typedef std::shared_ptr<FunctionObject> FunctionObjectPtr;