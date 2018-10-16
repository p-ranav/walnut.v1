#pragma once
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <string_literal_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <return_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <function_literal_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>

#include <object.hpp>
#include <integer_object.hpp>
#include <double_object.hpp>
#include <boolean_object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <return_object.hpp>
#include <function_object.hpp>

#include <environment.hpp>
#include <iostream>

struct Evaluator
{
  ObjectPtr Eval(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalInteger(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalDouble(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalBoolean(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalString(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalPrefixExpression(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalBangOperator(ObjectPtr right, EnvironmentPtr environment);
  ObjectPtr EvalUnaryMinusOperator(ObjectPtr right, EnvironmentPtr environment);

  ObjectPtr EvalInfixExpression(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalIntegerInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
  ObjectPtr EvalBooleanInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
  ObjectPtr EvalStringInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);

  ObjectPtr EvalBlockStatement(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalIfExpression(NodePtr node, EnvironmentPtr environment);
  bool IsTruth(ObjectPtr condition, EnvironmentPtr environment);
  ObjectPtr EvalReturnStatement(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalIdentifier(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalVarStatement(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalFunction(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalCallExpression(NodePtr node, EnvironmentPtr environment);
  std::vector<ObjectPtr> EvalExpressions(std::vector<NodePtr> expressions, EnvironmentPtr environment);
  ObjectPtr ApplyFunction(ObjectPtr function, std::vector<ObjectPtr> arguments);
  EnvironmentPtr ExtendFunctionEnvironment(FunctionObjectPtr function, std::vector<ObjectPtr> arguments);
  ObjectPtr UnwrapReturnValue(ObjectPtr object);
};