#include <evaluator.hpp>

ObjectPtr Evaluator::Eval(NodePtr node)
{
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
  }
  return std::make_shared<NullObject>();
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
  PrefixExpressionNodePtr prefix_expression_node = std::dynamic_pointer_cast<PrefixExpressionNode>(node);
  ObjectPtr right = Eval(prefix_expression_node->right);
  
  TokenType prefix_operator = prefix_expression_node->prefix_operator;
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
  {
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalInfixExpression(NodePtr node)
{
  return std::make_shared<NullObject>();
}