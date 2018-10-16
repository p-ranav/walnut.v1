#include <evaluator.hpp>

ObjectPtr Evaluator::Eval(NodePtr node)
{
  if (node == nullptr)
    return std::make_shared<NullObject>();

  switch (node->type)
  {
  case NodeType::INTEGER:
    return EvalInteger(node);
  case NodeType::DOUBLE:
    return EvalDouble(node);
  case NodeType::BOOLEAN:
    return EvalBoolean(node);
  case NodeType::STRING_LITERAL:
    return EvalString(node);
  case NodeType::PREFIX_EXPRESSION:
    return EvalPrefixExpression(node);
  case NodeType::INFIX_EXPRESSION:
    return EvalInfixExpression(node);
  case NodeType::IF_EXPRESSION:
    return EvalIfExpression(node);
  case NodeType::BLOCK_STATEMENT:
    return EvalBlockStatement(node);
  case NodeType::RETURN_STATEMENT:
    return EvalReturnStatement(node);
  default:
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalInteger(NodePtr node)
{
  IntegerNodePtr integer_node = std::dynamic_pointer_cast<IntegerNode>(node);
  return std::make_shared<IntegerObject>(integer_node->value);
}

ObjectPtr Evaluator::EvalDouble(NodePtr node)
{
  DoubleNodePtr double_node = std::dynamic_pointer_cast<DoubleNode>(node);
  return std::make_shared<DoubleObject>(double_node->value);
}

ObjectPtr Evaluator::EvalBoolean(NodePtr node)
{
  BooleanNodePtr boolean_node = std::dynamic_pointer_cast<BooleanNode>(node);
  return std::make_shared<BooleanObject>(boolean_node->value);
}

ObjectPtr Evaluator::EvalString(NodePtr node)
{
  StringLiteralNodePtr string_literal_node = std::dynamic_pointer_cast<StringLiteralNode>(node);
  return std::make_shared<StringObject>(string_literal_node->value);
}

ObjectPtr Evaluator::EvalPrefixExpression(NodePtr node)
{
  PrefixExpressionNodePtr expression = std::dynamic_pointer_cast<PrefixExpressionNode>(node);
  ObjectPtr right = Eval(expression->right);
  
  TokenType prefix_operator = expression->prefix_operator;
  switch (prefix_operator)
  {
  case TokenType::LOGICAL_NOT_OPERATOR:
    return EvalBangOperator(right);
  case TokenType::SUBTRACTION_OPERATOR:
    return EvalUnaryMinusOperator(right);
  default:
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalBangOperator(ObjectPtr right)
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

ObjectPtr Evaluator::EvalUnaryMinusOperator(ObjectPtr right)
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

ObjectPtr Evaluator::EvalInfixExpression(NodePtr node)
{
  InfixExpressionNodePtr expression = std::dynamic_pointer_cast<InfixExpressionNode>(node);
  ObjectPtr left = Eval(expression->left);
  ObjectPtr right = Eval(expression->right);
  TokenType infix_operator = expression->infix_operator;

  if (left->type == ObjectType::INTEGER && right->type == ObjectType::INTEGER)
    return EvalIntegerInfixExpression(infix_operator, left, right);
  else if (left->type == ObjectType::BOOLEAN && right->type == ObjectType::BOOLEAN)
    return EvalBooleanInfixExpression(infix_operator, left, right);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalIntegerInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right)
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

ObjectPtr Evaluator::EvalBooleanInfixExpression(TokenType infix_operator, ObjectPtr left, ObjectPtr right)
{
  BooleanObjectPtr left_node = std::dynamic_pointer_cast<BooleanObject>(left);
  BooleanObjectPtr right_node = std::dynamic_pointer_cast<BooleanObject>(right);
  bool left_value = left_node->value, right_value = right_node->value;

  if (infix_operator == TokenType::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == TokenType::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalBlockStatement(NodePtr node)
{
  ObjectPtr result = std::make_shared<NullObject>();

  BlockStatementNodePtr block = std::dynamic_pointer_cast<BlockStatementNode>(node);
  for (auto& statement : block->statements)
  {
    result = Eval(statement);

    if (result->type = ObjectType::RETURN)
      return result;
  }

  return result;
}

ObjectPtr Evaluator::EvalIfExpression(NodePtr node)
{
  IfExpressionNodePtr expression = std::dynamic_pointer_cast<IfExpressionNode>(node);
  ObjectPtr condition = Eval(expression->condition);
  
  if (IsTruth(condition))
    return Eval(expression->consequence);
  else
    return Eval(expression->alternative);
}

bool Evaluator::IsTruth(ObjectPtr condition)
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

ObjectPtr Evaluator::EvalReturnStatement(NodePtr node)
{
  ReturnStatementNodePtr statement = std::dynamic_pointer_cast<ReturnStatementNode>(node);
  return std::make_shared<ReturnObject>(Eval(statement->expression));
}

ObjectPtr Evaluator::EvalVarStatement(NodePtr node)
{
  VarStatementNodePtr statement = std::dynamic_pointer_cast<VarStatementNode>(node);
  ObjectPtr expression = Eval(statement->expression);
  // TODO: save value
  return std::make_shared<NullObject>();
}