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


struct Evaluator
{
  ObjectPtr Eval(NodePtr node);
  ObjectPtr EvalInteger(NodePtr node);
  ObjectPtr EvalDouble(NodePtr node);
  ObjectPtr EvalBoolean(NodePtr node);
  ObjectPtr EvalString(NodePtr node);

  ObjectPtr EvalPrefixExpression(NodePtr node);
  ObjectPtr EvalBangOperator(ObjectPtr right);
  ObjectPtr EvalUnaryMinusOperator(ObjectPtr right);

};