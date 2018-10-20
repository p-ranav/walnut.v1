#pragma once
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <string_literal_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <expression_assignment_statement_node.hpp>
#include <return_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <while_expression_node.hpp>
#include <for_expression_node.hpp>
#include <function_literal_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>
#include <array_literal_node.hpp>
#include <index_expression_node.hpp>

#include <object.hpp>
#include <integer_object.hpp>
#include <double_object.hpp>
#include <boolean_object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <return_object.hpp>
#include <function_object.hpp>
#include <builtin_function_object.hpp>
#include <array_object.hpp>

#include <environment.hpp>
#include <iostream>

struct Evaluator
{
  Evaluator();

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
  ObjectPtr EvalDoubleInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
  ObjectPtr EvalBooleanInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
  ObjectPtr EvalStringInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);

  ObjectPtr EvalBlockStatement(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalIfExpression(NodePtr node, EnvironmentPtr environment);
  bool IsTruth(ObjectPtr condition, EnvironmentPtr environment);
  ObjectPtr EvalWhileExpression(NodePtr node, EnvironmentPtr environment);
  
  ObjectPtr EvalForExpression(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalReturnStatement(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalIdentifier(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalVarStatement(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalExpressionAssignmentStatement(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalFunction(NodePtr node, EnvironmentPtr environment);

  ObjectPtr EvalCallExpression(NodePtr node, EnvironmentPtr environment);
  std::vector<ObjectPtr> EvalExpressions(std::vector<NodePtr> expressions, EnvironmentPtr environment);
  ObjectPtr ApplyFunction(ObjectPtr function, const std::vector<ObjectPtr>& arguments);
  EnvironmentPtr ExtendFunctionEnvironment(FunctionObjectPtr function, std::vector<ObjectPtr> arguments);
  ObjectPtr UnwrapReturnValue(ObjectPtr object);

  ObjectPtr EvalArrayLiteral(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalIndexOperator(NodePtr node, EnvironmentPtr environment);
  ObjectPtr EvalArrayIndexExpression(ObjectPtr array, ObjectPtr index);

  // Built-in Functions
  std::map<String, BuiltinFunctionObjectPtr> builtin_functions;
  ObjectPtr print(std::vector<ObjectPtr> arguments);
  ObjectPtr println(std::vector<ObjectPtr> arguments);
  ObjectPtr length(std::vector<ObjectPtr> arguments);

  ObjectPtr append(std::vector<ObjectPtr> arguments);
  ObjectPtr extend(std::vector<ObjectPtr> arguments);
  ObjectPtr map(std::vector<ObjectPtr> arguments);
  ObjectPtr filter(std::vector<ObjectPtr> arguments);
  ObjectPtr join(std::vector<ObjectPtr> arguments);
};