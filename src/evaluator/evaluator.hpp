#pragma once
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <string_literal_node.hpp>
#include <character_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <expression_assignment_statement_node.hpp>
#include <return_statement_node.hpp>
#include <import_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <while_expression_node.hpp>
#include <for_expression_node.hpp>
#include <function_literal_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>
#include <array_literal_node.hpp>
#include <index_expression_node.hpp>
#include <hash_literal_node.hpp>
#include <set_literal_node.hpp>
#include <tuple_node.hpp>
#include <key_value_argument_node.hpp>

#include <object.hpp>
#include <integer_object.hpp>
#include <double_object.hpp>
#include <boolean_object.hpp>
#include <character_object.hpp>
#include <string_object.hpp>
#include <null_object.hpp>
#include <return_object.hpp>
#include <function_object.hpp>
#include <builtin_function_object.hpp>
#include <array_object.hpp>
#include <range_object.hpp>
#include <hash_key.hpp>
#include <hash_object.hpp>
#include <set_object.hpp>
#include <tuple_object.hpp>
#include <key_value_argument_object.hpp>

#include <lexer.hpp>
#include <parser.hpp>
#include <environment.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <cstdint>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

namespace walnut
{

  struct Evaluator
  {
    Evaluator();
    ObjectPtr Eval(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalInteger(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalDouble(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalBoolean(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalCharacter(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalString(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalPrefixExpression(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalBangOperator(ObjectPtr right, EnvironmentPtr environment);
    ObjectPtr EvalUnaryMinusOperator(ObjectPtr right, EnvironmentPtr environment);

    ObjectPtr EvalInfixExpression(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalIntegerInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
    ObjectPtr EvalDoubleInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
    ObjectPtr EvalBooleanInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
    ObjectPtr EvalStringInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);
    ObjectPtr EvalCharacterInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment);

    ObjectPtr EvalBlockStatement(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalIfExpression(NodePtr node, EnvironmentPtr environment);
    bool IsTruth(ObjectPtr condition, EnvironmentPtr environment);

    ObjectPtr EvalWhileExpression(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalForExpression(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalReturnStatement(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalImportStatement(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalIdentifier(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalVarStatement(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalExpressionAssignmentStatement(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalFunction(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalCallExpression(NodePtr node, EnvironmentPtr environment);
    std::vector<ObjectPtr> EvalExpressions(std::vector<NodePtr> expressions, EnvironmentPtr environment);

    ObjectPtr ApplyFunction(ObjectPtr function, const std::vector<ObjectPtr> &arguments);
    EnvironmentPtr ExtendFunctionEnvironment(FunctionObjectPtr function, std::vector<ObjectPtr> arguments);
    ObjectPtr UnwrapReturnValue(ObjectPtr object);

    ObjectPtr EvalArrayLiteral(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalIndexOperator(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalArrayIndexExpression(ObjectPtr array, ObjectPtr index);

    ObjectPtr EvalHashLiteral(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalHashIndexExpression(ObjectPtr hash, ObjectPtr index);

    ObjectPtr EvalSetLiteral(NodePtr node, EnvironmentPtr environment);

    ObjectPtr EvalTuple(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalTupleIndexExpression(ObjectPtr array, ObjectPtr index);

    ObjectPtr EvalKeyValueArgument(NodePtr node, EnvironmentPtr environment);
    ObjectPtr EvalInExpression(NodePtr node, EnvironmentPtr environment);

    /* Built-in Functions */
    std::map<String, BuiltinFunctionObjectPtr> builtin_functions;
    ObjectPtr BuiltinPrint(std::vector<ObjectPtr> arguments);

    /* List/Sequence Functions */
    ObjectPtr BuiltinLength(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinAppend(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinExtend(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinInsert(std::vector<ObjectPtr> arguments);

    ObjectPtr BuiltinRange(std::vector<ObjectPtr> arguments);

    /* Map & Filter Functions */
    ObjectPtr BuiltinMap(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinFilter(std::vector<ObjectPtr> arguments);

    /* String Functions */
    ObjectPtr BuiltinFormat(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinSplit(std::vector<ObjectPtr> arguments);
    ObjectPtr BuiltinJoin(std::vector<ObjectPtr> arguments);
  };

}