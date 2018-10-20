#include <evaluator.hpp>
#include <math.h>

Evaluator::Evaluator()
{
  builtin_functions.insert(std::make_pair("print",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::print, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("length", 
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::length, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("append",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::append, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("extend",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::extend, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("map",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::map, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("filter",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::filter, this, std::placeholders::_1))));
  builtin_functions.insert(std::make_pair("join",
    std::make_shared<BuiltinFunctionObject>(std::bind(&Evaluator::join, this, std::placeholders::_1))));
}

ObjectPtr Evaluator::Eval(NodePtr node, EnvironmentPtr environment)
{
  if (node == nullptr)
    return std::make_shared<NullObject>();

  switch (node->type)
  {
  case NodeType::INTEGER:
    return EvalInteger(node, environment);
  case NodeType::DOUBLE:
    return EvalDouble(node, environment);
  case NodeType::BOOLEAN:
    return EvalBoolean(node, environment);
  case NodeType::STRING_LITERAL:
    return EvalString(node, environment);
  case NodeType::PREFIX_EXPRESSION:
    return EvalPrefixExpression(node, environment);
  case NodeType::INFIX_EXPRESSION:
    return EvalInfixExpression(node, environment);
  case NodeType::IF_EXPRESSION:
    return EvalIfExpression(node, environment);
  case NodeType::WHILE_EXPRESSION:
    return EvalWhileExpression(node, environment);
  case NodeType::FOR_EXPRESSION:
    return EvalForExpression(node, environment);
  case NodeType::BLOCK_STATEMENT:
    return EvalBlockStatement(node, environment);
  case NodeType::RETURN_STATEMENT:
    return EvalReturnStatement(node, environment);
  case NodeType::IDENTIFIER:
    return EvalIdentifier(node, environment);
  case NodeType::VAR_STATEMENT:
    return EvalVarStatement(node, environment);
  case NodeType::FUNCTION:
    return EvalFunction(node, environment);
  case NodeType::CALL_EXPRESSION:
    return EvalCallExpression(node, environment);
  case NodeType::ARRAY_LITERAL:
    return EvalArrayLiteral(node, environment);
  case NodeType::INDEX_EXPRESSION:
    return EvalIndexOperator(node, environment);
  default:
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalInteger(NodePtr node, EnvironmentPtr environment)
{
  IntegerNodePtr integer_node = std::dynamic_pointer_cast<IntegerNode>(node);
  return std::make_shared<IntegerObject>(integer_node->value);
}

ObjectPtr Evaluator::EvalDouble(NodePtr node, EnvironmentPtr environment)
{
  DoubleNodePtr double_node = std::dynamic_pointer_cast<DoubleNode>(node);
  return std::make_shared<DoubleObject>(double_node->value);
}

ObjectPtr Evaluator::EvalBoolean(NodePtr node, EnvironmentPtr environment)
{
  BooleanNodePtr boolean_node = std::dynamic_pointer_cast<BooleanNode>(node);
  return std::make_shared<BooleanObject>(boolean_node->value);
}

ObjectPtr Evaluator::EvalString(NodePtr node, EnvironmentPtr environment)
{
  StringLiteralNodePtr string_literal_node = std::dynamic_pointer_cast<StringLiteralNode>(node);
  return std::make_shared<StringObject>(string_literal_node->value);
}

ObjectPtr Evaluator::EvalPrefixExpression(NodePtr node, EnvironmentPtr environment)
{
  PrefixExpressionNodePtr expression = std::dynamic_pointer_cast<PrefixExpressionNode>(node);
  ObjectPtr right = Eval(expression->right, environment);
  
  TokenType prefix_operator = expression->prefix_operator;
  switch (prefix_operator)
  {
  case TokenType::LOGICAL_NOT_OPERATOR:
    return EvalBangOperator(right, environment);
  case TokenType::SUBTRACTION_OPERATOR:
    return EvalUnaryMinusOperator(right, environment);
  default:
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalBangOperator(ObjectPtr right, EnvironmentPtr environment)
{
  BooleanObjectPtr result = std::make_shared<BooleanObject>(false);

  if (right->type == ObjectType::NULL_)
    result->value = true;

  BooleanObjectPtr boolean_right = std::dynamic_pointer_cast<BooleanObject>(right);
  if (boolean_right != nullptr)
    if (boolean_right->value == false)
      result->value = true;

  return result;
}

ObjectPtr Evaluator::EvalUnaryMinusOperator(ObjectPtr right, EnvironmentPtr environment)
{
  if (right->type == ObjectType::INTEGER)
  {
    IntegerObjectPtr integer_right = std::dynamic_pointer_cast<IntegerObject>(right);
    integer_right->value *= -1;
    return integer_right;
  }
  else if (right->type == ObjectType::DOUBLE)
  {
    DoubleObjectPtr double_right = std::dynamic_pointer_cast<DoubleObject>(right);
    double_right->value *= -1;
    return double_right;
  }
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalInfixExpression(NodePtr node, EnvironmentPtr environment)
{
  InfixExpressionNodePtr expression = std::dynamic_pointer_cast<InfixExpressionNode>(node);
  ObjectPtr left = Eval(expression->left, environment);
  ObjectPtr right = Eval(expression->right, environment);
  TokenType infix_operator = expression->infix_operator;

  if (left->type == ObjectType::INTEGER && right->type == ObjectType::INTEGER)
    return EvalIntegerInfixExpression(infix_operator, left, right, environment);
  else if (left->type == ObjectType::INTEGER && right->type == ObjectType::DOUBLE)
  {
    IntegerObjectPtr left_object = std::dynamic_pointer_cast<IntegerObject>(left);
    return EvalDoubleInfixExpression(infix_operator, left_object->ToDouble(), right, environment);
  }
  else if (left->type == ObjectType::DOUBLE && right->type == ObjectType::INTEGER)
  {
    IntegerObjectPtr right_object = std::dynamic_pointer_cast<IntegerObject>(right);
    return EvalDoubleInfixExpression(infix_operator, left, right_object->ToDouble(), environment);
  }
  else if (left->type == ObjectType::DOUBLE && right->type == ObjectType::DOUBLE)
    return EvalDoubleInfixExpression(infix_operator, left, right, environment);
  else if (left->type == ObjectType::BOOLEAN && right->type == ObjectType::BOOLEAN)
    return EvalBooleanInfixExpression(infix_operator, left, right, environment);
  else if (left->type == ObjectType::STRING && right->type == ObjectType::STRING)
    return EvalStringInfixExpression(infix_operator, left, right, environment);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalIntegerInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  IntegerObjectPtr left_node = std::dynamic_pointer_cast<IntegerObject>(left);
  IntegerObjectPtr right_node = std::dynamic_pointer_cast<IntegerObject>(right);
  int left_value = left_node->value, right_value = right_node->value;

  // arithmetic operations
  if (infix_operator == TokenType::ADDITION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value + right_value);
  else if (infix_operator == TokenType::SUBTRACTION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value - right_value);
  else if (infix_operator == TokenType::MULTIPLICATION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value * right_value);
  else if (infix_operator == TokenType::DIVISION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value / right_value);
  else if (infix_operator == TokenType::MODULUS_OPERATOR)
    return std::make_shared<IntegerObject>(left_value % right_value);

  // logical operations
  else if (infix_operator == TokenType::GREATER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value > right_value);
  else if (infix_operator == TokenType::GREATER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value >= right_value);
  else if (infix_operator == TokenType::LESSER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value < right_value);
  else if (infix_operator == TokenType::LESSER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value <= right_value);
  else if (infix_operator == TokenType::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == TokenType::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalDoubleInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  DoubleObjectPtr left_node = std::dynamic_pointer_cast<DoubleObject>(left);
  DoubleObjectPtr right_node = std::dynamic_pointer_cast<DoubleObject>(right);
  double left_value = left_node->value, right_value = right_node->value;

  // arithmetic operations
  if (infix_operator == TokenType::ADDITION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value + right_value);
  else if (infix_operator == TokenType::SUBTRACTION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value - right_value);
  else if (infix_operator == TokenType::MULTIPLICATION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value * right_value);
  else if (infix_operator == TokenType::DIVISION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value / right_value);
  else if (infix_operator == TokenType::MODULUS_OPERATOR)
    return std::make_shared<DoubleObject>(fmod(left_value, right_value));

  // logical operations
  else if (infix_operator == TokenType::GREATER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value > right_value);
  else if (infix_operator == TokenType::GREATER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value >= right_value);
  else if (infix_operator == TokenType::LESSER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value < right_value);
  else if (infix_operator == TokenType::LESSER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value <= right_value);
  else if (infix_operator == TokenType::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == TokenType::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalBooleanInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  BooleanObjectPtr left_node = std::dynamic_pointer_cast<BooleanObject>(left);
  BooleanObjectPtr right_node = std::dynamic_pointer_cast<BooleanObject>(right);
  bool left_value = left_node->value, right_value = right_node->value;

  if (infix_operator == TokenType::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == TokenType::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == TokenType::LOGICAL_AND_OPERATOR)
  {
    if (left_value == false || right_value == false)
      return std::make_shared<BooleanObject>(false);
    else
      return std::make_shared<BooleanObject>(true);
  }
  else if (infix_operator == TokenType::LOGICAL_OR_OPERATOR)
  {
    if (left_value == true || right_value == true)
      return std::make_shared<BooleanObject>(true);
    else
      return std::make_shared<BooleanObject>(false);
  }
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalStringInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  StringObjectPtr left_node = std::dynamic_pointer_cast<StringObject>(left);
  StringObjectPtr right_node = std::dynamic_pointer_cast<StringObject>(right);
  String left_value = left_node->value, right_value = right_node->value;

  if (infix_operator == TokenType::ADDITION_OPERATOR)
    return std::make_shared<StringObject>(left_value + right_value);
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalBlockStatement(NodePtr node, EnvironmentPtr environment)
{
  ObjectPtr result = std::make_shared<NullObject>();

  BlockStatementNodePtr block = std::dynamic_pointer_cast<BlockStatementNode>(node);
  for (auto& statement : block->statements)
  {
    result = Eval(statement, environment);

    if (result->type == ObjectType::RETURN)
      return result;
  }

  return result;
}

ObjectPtr Evaluator::EvalIfExpression(NodePtr node, EnvironmentPtr environment)
{
  IfExpressionNodePtr expression = std::dynamic_pointer_cast<IfExpressionNode>(node);
  ObjectPtr condition = Eval(expression->condition, environment);
  
  if (IsTruth(condition, environment))
    return Eval(expression->consequence, environment);
  else
    return Eval(expression->alternative, environment);
}

bool Evaluator::IsTruth(ObjectPtr condition, EnvironmentPtr environment)
{
  if (condition->type == ObjectType::BOOLEAN)
  {
    BooleanObjectPtr boolean_condition = std::dynamic_pointer_cast<BooleanObject>(condition);
    return (boolean_condition->value == true);
  }
  else if (condition->type == ObjectType::NULL_)
  {
    return false;
  }
  else if (condition->type == ObjectType::INTEGER)
  {
    IntegerNodePtr integer_condition = std::dynamic_pointer_cast<IntegerNode>(condition);
    return (integer_condition->value != 0);
  }
  else if (condition->type == ObjectType::DOUBLE)
  {
    DoubleNodePtr double_condition = std::dynamic_pointer_cast<DoubleNode>(condition);
    return (double_condition->value != 0.0);
  }
  else
    return true;
}

ObjectPtr Evaluator::EvalWhileExpression(NodePtr node, EnvironmentPtr environment)
{
  WhileExpressionNodePtr expression = std::dynamic_pointer_cast<WhileExpressionNode>(node);
  ObjectPtr result = std::make_shared<NullObject>();

  EnvironmentPtr while_environment = std::make_shared<Environment>();
  while_environment->outer = environment;
  
  while (IsTruth(Eval(expression->condition, while_environment), while_environment))
  {
    result = Eval(expression->consequence, while_environment);
    if (result->type == ObjectType::RETURN)
      return result;
  }

  for (auto& kv : environment->store)
  {
    if (while_environment->store.find(kv.first) != while_environment->store.end())
    {
      environment->Set(kv.first, while_environment->Get(kv.first));
    }
  }

  return result;
}

ObjectPtr Evaluator::EvalForExpression(NodePtr node, EnvironmentPtr environment)
{
  ForExpressionNodePtr expression = std::dynamic_pointer_cast<ForExpressionNode>(node);
  ObjectPtr result = std::make_shared<NullObject>();

  ObjectPtr iterable = Eval(expression->iterable, environment);

  // Iterable is an array - It could be an array of anything:
  if (iterable->type == ObjectType::ARRAY)
  {
    ArrayObjectPtr iterable_list = std::dynamic_pointer_cast<ArrayObject>(iterable);
    EnvironmentPtr for_environment = std::make_shared<Environment>();
    for_environment->outer = environment;

    for (size_t i = 0; i < iterable_list->elements.size(); i++)
    {
      /* Initialize/update iterator values */

      // We have just one iterator
      if (expression->iterators.size() == 1)
      {
        IdentifierNodePtr iterator = std::dynamic_pointer_cast<IdentifierNode>(expression->iterators[0]);
        if (iterator)
        {
          ObjectPtr iterable_value = (iterable_list->elements)[i];
          for_environment->Set(iterator->value, iterable_value);
        }
      }
      else if (expression->iterators.size() > 1)
      {
        ObjectPtr iterable_value = (iterable_list->elements)[i];

        // Check if iterable_value is itself an iterable
        if (iterable_value->type == ObjectType::ARRAY)
        {
          ArrayObjectPtr iterable_value_list = std::dynamic_pointer_cast<ArrayObject>(iterable_value);
          if (iterable_value_list->elements.size() == expression->iterators.size())
          {
            for (size_t j = 0; j < expression->iterators.size(); j++)
            {
              IdentifierNodePtr iterator = std::dynamic_pointer_cast<IdentifierNode>(expression->iterators[j]);
              ObjectPtr iterable_value = (iterable_value_list->elements)[j];
              for_environment->Set(iterator->value, iterable_value);
            }
          }
        }
        // TODO: else if (iterable_value->type == NodeType::DICTIONARY)

      }

      // Evaluate body of for loop using iterator values set in for_environment
      result = Eval(expression->body, for_environment);
      if (result->type == ObjectType::RETURN)
        return result;
    }

    for (auto& kv : environment->store)
    {
      if (for_environment->store.find(kv.first) != for_environment->store.end())
      {
        environment->Set(kv.first, for_environment->Get(kv.first));
      }
    }

  }

  return result;
}

ObjectPtr Evaluator::EvalReturnStatement(NodePtr node, EnvironmentPtr environment)
{
  ReturnStatementNodePtr statement = std::dynamic_pointer_cast<ReturnStatementNode>(node);
  return std::make_shared<ReturnObject>(Eval(statement->expression, environment));
}

ObjectPtr Evaluator::EvalIdentifier(NodePtr node, EnvironmentPtr environment)
{
  IdentifierNodePtr identifier_node = std::dynamic_pointer_cast<IdentifierNode>(node);

  if (builtin_functions.find(identifier_node->value) != builtin_functions.end())
    return builtin_functions[identifier_node->value];

  ObjectPtr environment_lookup = environment->Get(identifier_node->value);

  if (!environment_lookup)
  {
    std::cout << "Identifier not found: " << identifier_node->value << std::endl;
    return std::make_shared<NullObject>();
  }
  else
    return environment_lookup;
}

ObjectPtr Evaluator::EvalVarStatement(NodePtr node, EnvironmentPtr environment)
{
  VarStatementNodePtr statement = std::dynamic_pointer_cast<VarStatementNode>(node);
  ObjectPtr value;
  if (statement->expression)
    value = Eval(statement->expression, environment);
  else
    value = std::make_shared<NullObject>();
  environment->Set(statement->name->value, value);
  return value;
}

ObjectPtr Evaluator::EvalFunction(NodePtr node, EnvironmentPtr environment)
{
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(node);
  return std::make_shared<FunctionObject>(function->parameters, function->body, environment);
}

ObjectPtr Evaluator::EvalCallExpression(NodePtr node, EnvironmentPtr environment)
{
  CallExpressionNodePtr expression = std::dynamic_pointer_cast<CallExpressionNode>(node);
  FunctionLiteralNodePtr call_function = std::dynamic_pointer_cast<FunctionLiteralNode>(expression->function);
  ObjectPtr function = Eval(expression->function, environment);
  std::vector<ObjectPtr> arguments = EvalExpressions(expression->arguments, environment);
  return ApplyFunction(function, arguments);
}

std::vector<ObjectPtr> Evaluator::EvalExpressions(std::vector<NodePtr> expressions, EnvironmentPtr environment)
{
  std::vector<ObjectPtr> result;
  for (auto& expression : expressions)
    result.push_back(Eval(expression, environment));
  return result;
}

ObjectPtr Evaluator::ApplyFunction(ObjectPtr function, const std::vector<ObjectPtr>& arguments)
{
  if (function->type != ObjectType::FUNCTION && function->type != ObjectType::BUILTIN_FUNCTION)
    std::cout << "not a function" << std::endl;

  if (function->type == ObjectType::FUNCTION)
  {
    FunctionObjectPtr function_object = std::dynamic_pointer_cast<FunctionObject>(function);
    EnvironmentPtr extended_environment = ExtendFunctionEnvironment(function_object, arguments);
    ObjectPtr evaluated = Eval(function_object->body, extended_environment);
    return UnwrapReturnValue(evaluated);
  }
  else if (function->type == ObjectType::BUILTIN_FUNCTION)
  {
    BuiltinFunctionObjectPtr function_object = std::dynamic_pointer_cast<BuiltinFunctionObject>(function);
    return function_object->function(arguments);
  }
  else
    return std::make_shared<NullObject>();
}

EnvironmentPtr Evaluator::ExtendFunctionEnvironment(FunctionObjectPtr function, std::vector<ObjectPtr> arguments)
{
  EnvironmentPtr environment = std::make_shared<Environment>(function->environment);
  for (size_t i = 0; i < function->parameters.size(); i++)
  {
    if (function->parameters[i])
      environment->Set(function->parameters[i]->value, arguments[i]);
  }
  return environment;
}

ObjectPtr Evaluator::UnwrapReturnValue(ObjectPtr object)
{
  if (object->type == ObjectType::RETURN)
  {
    ReturnObjectPtr result = std::dynamic_pointer_cast<ReturnObject>(object);
    return result->value;
  }
  return object;
}

ObjectPtr Evaluator::EvalArrayLiteral(NodePtr node, EnvironmentPtr environment)
{
  ArrayLiteralNodePtr array_node = std::dynamic_pointer_cast<ArrayLiteralNode>(node);
  return std::make_shared<ArrayObject>(EvalExpressions(array_node->elements, environment));
}

ObjectPtr Evaluator::EvalIndexOperator(NodePtr node, EnvironmentPtr environment)
{
  IndexExpressionNodePtr expression = std::dynamic_pointer_cast<IndexExpressionNode>(node);
  ObjectPtr left = Eval(expression->left, environment);
  ObjectPtr index = Eval(expression->index, environment);

  if (left->type == ObjectType::ARRAY && index->type == Object::INTEGER)
  {
    return EvalArrayIndexExpression(left, index);
  }
  else
  {
    std::cout << "error: index operator not supported" << std::endl;
    return std::make_shared<NullObject>();
  }

}

ObjectPtr Evaluator::EvalArrayIndexExpression(ObjectPtr array, ObjectPtr index)
{
  ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(array);
  std::vector<ObjectPtr> elements = array_object->elements;
  int array_size = static_cast<int>(elements.size());

  IntegerObjectPtr array_index = std::dynamic_pointer_cast<IntegerObject>(index);
  int index_value = array_index->value;

  if (index_value >= array_size)
  {
    std::cout << "error: array index out of range" << std::endl;
    return std::make_shared<NullObject>();
  }
  else if (index_value < 0)
  {
    std::cout << "error: array index cannot be negative" << std::endl;
    return std::make_shared<NullObject>();
  }
  return elements[index_value];
}