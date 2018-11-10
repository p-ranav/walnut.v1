#include <evaluator.hpp>
#include <math.h>
#include <utf8.hpp>

namespace walnut
{

#define BUILTIN(label, function)               \
  builtin_functions.insert(std::make_pair(     \
      label,                                   \
      std::make_shared<BuiltinFunctionObject>( \
          std::bind(&Evaluator::               \
                        function,              \
                    this, std::placeholders::_1))));

Evaluator::Evaluator(StringConstRef buffer) : buffer(buffer)
{
  BUILTIN("print", BuiltinPrint);
  BUILTIN("type", BuiltinType);

  BUILTIN("length", BuiltinLength);
  BUILTIN("append", BuiltinAppend);
  BUILTIN("extend", BuiltinExtend);
  BUILTIN("insert", BuiltinInsert);

  BUILTIN("range", BuiltinRange);
  BUILTIN("map", BuiltinMap);
  BUILTIN("filter", BuiltinFilter);
  BUILTIN("enumerate", BuiltinEnumerate);

  BUILTIN("format", BuiltinFormat);
  BUILTIN("split", BuiltinSplit);
  BUILTIN("join", BuiltinJoin);
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
  case NodeType::CHARACTER:
    return EvalCharacter(node, environment);
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
  case NodeType::IMPORT_STATEMENT:
    return EvalImportStatement(node, environment);
  case NodeType::IDENTIFIER:
    return EvalIdentifier(node, environment);
  case NodeType::VAR_STATEMENT:
    return EvalVarStatement(node, environment);
  case NodeType::EXPRESSION_ASSIGNMENT_STATEMENT:
    return EvalExpressionAssignmentStatement(node, environment);
  case NodeType::FUNCTION:
    return EvalFunction(node, environment);
  case NodeType::CALL_EXPRESSION:
    return EvalCallExpression(node, environment);
  case NodeType::ARRAY_LITERAL:
    return EvalArrayLiteral(node, environment);
  case NodeType::INDEX_EXPRESSION:
    return EvalIndexOperator(node, environment);
  case NodeType::HASH_LITERAL:
    return EvalHashLiteral(node, environment);
  case NodeType::SET_LITERAL:
    return EvalSetLiteral(node, environment);
  case NodeType::TUPLE:
    return EvalTuple(node, environment);
  case NodeType::KEY_VALUE_ARGUMENT:
    return EvalKeyValueArgument(node, environment);
  case NodeType::IN_EXPRESSION:
    return EvalInExpression(node, environment);
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

ObjectPtr Evaluator::EvalCharacter(NodePtr node, EnvironmentPtr environment)
{
  CharacterNodePtr character_node = std::dynamic_pointer_cast<CharacterNode>(node);
  return std::make_shared<CharacterObject>(character_node->value);
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

  Token::Type prefix_operator = expression->prefix_operator;
  switch (prefix_operator)
  {
  case Token::Type::LOGICAL_NOT_OPERATOR:
    return EvalBangOperator(right, environment);
  case Token::Type::SUBTRACTION_OPERATOR:
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

  else if (right->type == ObjectType::BOOLEAN)
  {
    BooleanObjectPtr boolean_right = std::dynamic_pointer_cast<BooleanObject>(right);
    if (boolean_right != nullptr)
      if (boolean_right->value == false)
        result->value = true;
  }
  else if (right->type == ObjectType::INTEGER)
  {
    IntegerObjectPtr integer_right = std::dynamic_pointer_cast<IntegerObject>(right);
    if (integer_right != nullptr)
      if (integer_right->value == 0)
        result->value = true;
  }
  else if (right->type == ObjectType::DOUBLE)
  {
    DoubleObjectPtr double_right = std::dynamic_pointer_cast<DoubleObject>(right);
    if (double_right != nullptr)
      if (double_right->value == 0)
        result->value = true;
  }

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
  Token::Type infix_operator = expression->infix_operator;

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
  else if (left->type == ObjectType::CHARACTER && right->type == ObjectType::CHARACTER)
    return EvalCharacterInfixExpression(infix_operator, left, right, environment);

  else
  {
    if (infix_operator == Token::Type::EQUALITY_OPERATOR)
      return std::make_shared<BooleanObject>(false);
    else if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
      return std::make_shared<BooleanObject>(true);
    else
      return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalIntegerInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  IntegerObjectPtr left_node = std::dynamic_pointer_cast<IntegerObject>(left);
  IntegerObjectPtr right_node = std::dynamic_pointer_cast<IntegerObject>(right);
  int64_t left_value = left_node->value, right_value = right_node->value;

  // arithmetic operations
  if (infix_operator == Token::Type::ADDITION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value + right_value);
  else if (infix_operator == Token::Type::SUBTRACTION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value - right_value);
  else if (infix_operator == Token::Type::MULTIPLICATION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value * right_value);
  else if (infix_operator == Token::Type::DIVISION_OPERATOR)
    return std::make_shared<IntegerObject>(left_value / right_value);
  else if (infix_operator == Token::Type::MODULUS_OPERATOR)
    return std::make_shared<IntegerObject>(left_value % right_value);

  // logical operations
  else if (infix_operator == Token::Type::GREATER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value > right_value);
  else if (infix_operator == Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value >= right_value);
  else if (infix_operator == Token::Type::LESSER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value < right_value);
  else if (infix_operator == Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value <= right_value);
  else if (infix_operator == Token::Type::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalDoubleInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  DoubleObjectPtr left_node = std::dynamic_pointer_cast<DoubleObject>(left);
  DoubleObjectPtr right_node = std::dynamic_pointer_cast<DoubleObject>(right);
  double left_value = left_node->value, right_value = right_node->value;

  // arithmetic operations
  if (infix_operator == Token::Type::ADDITION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value + right_value);
  else if (infix_operator == Token::Type::SUBTRACTION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value - right_value);
  else if (infix_operator == Token::Type::MULTIPLICATION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value * right_value);
  else if (infix_operator == Token::Type::DIVISION_OPERATOR)
    return std::make_shared<DoubleObject>(left_value / right_value);
  else if (infix_operator == Token::Type::MODULUS_OPERATOR)
    return std::make_shared<DoubleObject>(fmod(left_value, right_value));

  // logical operations
  else if (infix_operator == Token::Type::GREATER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value > right_value);
  else if (infix_operator == Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value >= right_value);
  else if (infix_operator == Token::Type::LESSER_THAN_OPERATOR)
    return std::make_shared<BooleanObject>(left_value < right_value);
  else if (infix_operator == Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR)
    return std::make_shared<BooleanObject>(left_value <= right_value);
  else if (infix_operator == Token::Type::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);

  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalBooleanInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  BooleanObjectPtr left_node = std::dynamic_pointer_cast<BooleanObject>(left);
  BooleanObjectPtr right_node = std::dynamic_pointer_cast<BooleanObject>(right);
  bool left_value = left_node->value, right_value = right_node->value;

  if (infix_operator == Token::Type::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == Token::Type::LOGICAL_AND_OPERATOR)
  {
    if (left_value == false || right_value == false)
      return std::make_shared<BooleanObject>(false);
    else
      return std::make_shared<BooleanObject>(true);
  }
  else if (infix_operator == Token::Type::LOGICAL_OR_OPERATOR)
  {
    if (left_value == true || right_value == true)
      return std::make_shared<BooleanObject>(true);
    else
      return std::make_shared<BooleanObject>(false);
  }
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalStringInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  StringObjectPtr left_node = std::dynamic_pointer_cast<StringObject>(left);
  StringObjectPtr right_node = std::dynamic_pointer_cast<StringObject>(right);
  String left_value = left_node->Value(), right_value = right_node->Value();

  if (infix_operator == Token::Type::ADDITION_OPERATOR)
    return std::make_shared<StringObject>(left_value + right_value);
  else if (infix_operator == Token::Type::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  else if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalCharacterInfixExpression(Token::Type infix_operator, ObjectPtr left, ObjectPtr right, EnvironmentPtr environment)
{
  CharacterObjectPtr left_node = std::dynamic_pointer_cast<CharacterObject>(left);
  CharacterObjectPtr right_node = std::dynamic_pointer_cast<CharacterObject>(right);
  String left_value = left_node->Value(), right_value = right_node->Value();

  if (infix_operator == Token::Type::EQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value == right_value);
  if (infix_operator == Token::Type::INEQUALITY_OPERATOR)
    return std::make_shared<BooleanObject>(left_value != right_value);
  else
    return std::make_shared<NullObject>();
}

ObjectPtr Evaluator::EvalInExpression(NodePtr node, EnvironmentPtr environment)
{
  InExpressionNodePtr expression = std::dynamic_pointer_cast<InExpressionNode>(node);
  NodePtr iterator = expression->iterator;
  NodePtr iterable = expression->iterable;

  ObjectPtr left = Eval(iterator, environment);
  ObjectPtr right = Eval(iterable, environment);
  bool result = false;
  if (right->iterable == true)
  {
    if (right->type == ObjectType::HASH)
    {
      HashObjectPtr hash = std::dynamic_pointer_cast<HashObject>(right);
      try
      {
        HashPair search = hash->Get(Hash(left));
        if (search.value != nullptr)
          result = true;
      }
      catch (...)
      {
        result = false;
      }
    }
    else if (right->type == ObjectType::STRING)
    {
      StringObjectPtr string = std::dynamic_pointer_cast<StringObject>(right);
      if (left->type == ObjectType::STRING)
      {
        StringObjectPtr left_string = std::dynamic_pointer_cast<StringObject>(left);
        if (contains(string->Value(), left_string->Value()))
          result = true;
      }
      else if (left->type == ObjectType::CHARACTER)
      {
        CharacterObjectPtr left_string = std::dynamic_pointer_cast<CharacterObject>(left);
        if (contains(string->Value(), left_string->Value()))
          result = true;
      }
      else
        result = false;
    }
    else
    {
      right->IterableInit();
      do
      {
        ObjectPtr current_value = right->IterableCurrentValue();
        if (!expression->negate_result)
        {
          if (left->Inspect() == current_value->Inspect())
          {
            result = true;
            break;
          }
        }
        else
        {
          if (left->Inspect() == current_value->Inspect())
          {
            result = false;
            break;
          }
          else
          {
            result = true;
          }
        }
      } while (right->IterableNext() != right->IterableEnd());
    }
  }
  return std::make_shared<BooleanObject>(result);
}

ObjectPtr Evaluator::EvalBlockStatement(NodePtr node, EnvironmentPtr environment)
{
  ObjectPtr result = std::make_shared<NullObject>();

  BlockStatementNodePtr block = std::dynamic_pointer_cast<BlockStatementNode>(node);
  for (auto &statement : block->statements)
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
  for (size_t i = 0; i < expression->conditions.size(); i++)
  {
    ObjectPtr condition = Eval(expression->conditions[i], environment);
    if (IsTruth(condition, environment))
      return Eval(expression->consequences[i], environment);
  }
  if (expression->alternative != nullptr)
    return Eval(expression->alternative, environment);
  else
    return std::make_shared<NullObject>();
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

  while (true)
  {
    NodePtr condition = expression->condition;
    ObjectPtr condition_result = Eval(condition, while_environment);

    if (!IsTruth(condition_result, while_environment))
      break;

    NodePtr consequence = expression->consequence;
    ObjectPtr consequence_result = Eval(consequence, while_environment);
    if (consequence_result->type == ObjectType::RETURN)
      return consequence_result;
    else
      result = consequence_result;
  }

  std::vector<EnvironmentPtr> environments = {environment};
  EnvironmentPtr outer_environment = environment->outer;
  while (outer_environment != nullptr)
  {
    environments.push_back(outer_environment);
    outer_environment = outer_environment->outer;
  }

  for (auto &nested_environment : environments)
  {
    for (auto &kv : nested_environment->store)
    {
      if (while_environment->store.find(kv.first) != while_environment->store.end())
      {
        nested_environment->Set(kv.first, while_environment->Get(kv.first));
        while_environment->store.erase(kv.first);
      }
    }
  }

  return result;
}

ObjectPtr Evaluator::EvalForExpression(NodePtr node, EnvironmentPtr environment)
{
  ObjectPtr result = std::make_shared<NullObject>();
  EnvironmentPtr for_environment = std::make_shared<Environment>();
  for_environment->outer = environment;

  ForExpressionNodePtr expression = std::dynamic_pointer_cast<ForExpressionNode>(node);
  ObjectPtr eval_result = Eval(expression->iterable, environment);
  ObjectPtr expression_object = eval_result->Copy();

  if (expression_object->iterable == true)
  {
    expression_object->IterableInit();
    do
    {
      // Set value of each parameter in for expression
      // Update environment
      ObjectPtr current_value = expression_object->IterableCurrentValue();

      if (current_value != nullptr)
      {
        if (current_value->iterable == false)
        {
          // Example: for x in [1, 2, 3, 4, 5]
          // current_value = 1
          // 1 is not iterable, so we're here
          if (expression->iterators.size() != 1)
          {
            // TODO: report error
          }
          IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(expression->iterators[0]);
          for_environment->Set(identifier->value, current_value);
        }
        else
        {
          current_value->IterableInit();
          // Example: for x, y in [[1, 2], [3, 4]]
          // current_value = [1, 2]
          // [1, 2] is iterable
          if (expression->iterators.size() == 1)
          {
            // Example: for x in [[1, 2], [3, 4]]
            // iterators size is just 1, i.e., x
            // simply set x to [1, 2] and move on
            IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(expression->iterators[0]);
            for_environment->Set(identifier->value, current_value);
          }
          else if (expression->iterators.size() > 1)
          {
            if (expression->iterators.size() != current_value->IterableSize())
            {
              // We're here because you typed:
              // for a, b in [[1, 2, 3], [4, 5, 6]]
              // a, b      => size 2
              // [1, 2, 3] => size 3
              // TODO: report error
            }

            // Example: for a, b, c in [[1, 2, 3], [4, 5, 6]]
            // current_value = [1, 2, 3]
            // we need to set a = 1, b = 2 , c = 3
            size_t index = 0;
            do
            {
              IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(expression->iterators[index]);
              for_environment->Set(identifier->value, current_value->IterableCurrentValue());
              index += 1;
            } while (current_value->IterableNext() != current_value->IterableEnd());
          }
        }
      }

      // Evaluate body of for loop using iterator values set in for_environment
      result = Eval(expression->body, for_environment);
      if (result->type == ObjectType::RETURN)
        return result;

    } while (expression_object->IterableNext() != expression_object->IterableEnd());
  }

  std::vector<EnvironmentPtr> environments = {environment};
  EnvironmentPtr outer_environment = environment->outer;
  while (outer_environment != nullptr)
  {
    environments.push_back(outer_environment);
    outer_environment = outer_environment->outer;
  }

  for (auto &nested_environment : environments)
  {
    for (auto &kv : nested_environment->store)
    {
      if (for_environment->store.find(kv.first) != for_environment->store.end())
      {
        nested_environment->Set(kv.first, for_environment->Get(kv.first));
        for_environment->store.erase(kv.first);
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

ObjectPtr Evaluator::EvalImportStatement(NodePtr node, EnvironmentPtr environment)
{

  fs::path current_token_filename(node->token.file);
  fs::path current_token_working_directory = current_token_filename.parent_path();

  ImportStatementNodePtr import_statement_node = std::dynamic_pointer_cast<ImportStatementNode>(node);
  if (node == nullptr)
    return std::make_shared<NullObject>();

  InputFileStream file_stream;
  String filename = (current_token_working_directory / import_statement_node->value).string();
  String buffer;
  try
  {
    file_stream = InputFileStream(filename);
    buffer = String((EndOfStreamIterator(file_stream)), EndOfStreamIterator());
  }
  catch (...)
  {
    std::cout << "evaluator error: failed to import " << filename << std::endl;
  }

  Lexer lexer(filename, buffer);
  lexer.Tokenize();

  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();

  Evaluator evaluator(buffer);
  for (auto &statement : parser.statements)
  {
    walnut::ObjectPtr result = evaluator.Eval(statement, environment);
    if (result->type == walnut::ObjectType::RETURN)
      break;
  }
  lexer.tokens.clear();
  parser.statements.clear();
  return std::make_shared<NullObject>();
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

  if (statement->statement_type == VarStatementNode::StatementType::INITIALIZATION)
  {
    environment->Set(statement->name->value, value);
  }
  else if (statement->statement_type == VarStatementNode::StatementType::ASSIGNMENT)
  {
    ObjectPtr variable = environment->Get(statement->name->value);
    if (variable == nullptr)
    {
      std::cout << "evaluator error: variable " << statement->name->value << " doesn't exist" << std::endl;
    }
    else
    {
      EnvironmentPtr var_environment = environment;
      while (var_environment != nullptr && var_environment->store.find(statement->name->value) == var_environment->store.end())
      {
        var_environment = var_environment->outer;
      }
      var_environment->Set(statement->name->value, value);
    }
  }
  return value;
}

ObjectPtr Evaluator::EvalExpressionAssignmentStatement(NodePtr node, EnvironmentPtr environment)
{
  ExpressionAssignmentStatementNodePtr statement =
      std::dynamic_pointer_cast<ExpressionAssignmentStatementNode>(node);

  NodePtr left_expression = statement->left;
  if (left_expression->type == NodeType::INDEX_EXPRESSION)
  {
    IndexExpressionNodePtr index_expression = std::dynamic_pointer_cast<IndexExpressionNode>(left_expression);
    NodePtr identifier = index_expression->left;
    ObjectPtr identifier_object = Eval(identifier, environment);

    NodePtr index = index_expression->index;
    ObjectPtr index_object = Eval(index, environment);

    // If left is an array index expression
    if (identifier_object != nullptr && identifier_object->type == ObjectType::ARRAY && index_object->type == ObjectType::INTEGER)
    {
      ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(identifier_object);
      IntegerObjectPtr integer_object = std::dynamic_pointer_cast<IntegerObject>(index_object);
      if (integer_object->value < static_cast<int64_t>(array_object->elements.size()))
      {
        array_object->elements[static_cast<size_t>(integer_object->value)] = Eval(statement->expression, environment);
      }
      return array_object;
    }

    else if (identifier_object != nullptr && identifier_object->type == ObjectType::TUPLE && index_object->type == ObjectType::INTEGER)
    {
      return identifier_object; // tuples can't be mutated
    }

    else if (identifier_object != nullptr && identifier_object->type == ObjectType::HASH)
    {
      HashObjectPtr hash_object = std::dynamic_pointer_cast<HashObject>(identifier_object);
      try
      {
        HashPair &pair = hash_object->Get(Hash(index_object));
        pair.value = Eval(statement->expression, environment);
        return hash_object;
      }
      catch(...)
      {
        HashPair new_pair(index_object, Eval(statement->expression, environment));
        hash_object->Set(Hash(index_object), new_pair);
      }
    }

    else
    {
      std::cout << "error: index operator not supported " << std::endl;
      exit(EXIT_FAILURE);
      return identifier_object;
    }
  }

  return std::make_shared<NullObject>();
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
  std::vector<ObjectPtr> arguments = EvalExpressions(expression->arguments->elements, environment);
  return ApplyFunction(function, arguments);
}

std::vector<ObjectPtr> Evaluator::EvalExpressions(std::vector<NodePtr> expressions, EnvironmentPtr environment)
{
  std::vector<ObjectPtr> result;
  for (auto &expression : expressions)
    result.push_back(Eval(expression, environment));
  return result;
}

ObjectPtr Evaluator::ApplyFunction(ObjectPtr function, const std::vector<ObjectPtr> &arguments)
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
  if (left->type == ObjectType::TUPLE && index->type == Object::INTEGER)
  {
    return EvalTupleIndexExpression(left, index);
  }
  if (left->type == ObjectType::HASH)
  {
    return EvalHashIndexExpression(left, index);
  }
  else
  {
    std::cout << "error: index operator not supported " << std::endl;
    exit(EXIT_FAILURE);
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalArrayIndexExpression(ObjectPtr array, ObjectPtr index)
{
  ArrayObjectPtr array_object = std::dynamic_pointer_cast<ArrayObject>(array);
  std::vector<ObjectPtr> &elements = array_object->elements;
  int array_size = static_cast<int>(elements.size());

  IntegerObjectPtr array_index = std::dynamic_pointer_cast<IntegerObject>(index);
  int64_t index_value = array_index->value;

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
  return elements[static_cast<size_t>(index_value)];
}

ObjectPtr Evaluator::EvalHashLiteral(NodePtr node, EnvironmentPtr environment)
{
  HashObjectPtr result = std::make_shared<HashObject>();
  HashLiteralNodePtr hash_literal_node = std::dynamic_pointer_cast<HashLiteralNode>(node);

  for (auto &pair : hash_literal_node->pairs)
  {
    ObjectPtr key = Eval(pair.first, environment);
    if (!key->hashable)
    {
      std::cout << "evaluator error: key " << key->Inspect() << " is not hashable" << std::endl;
      return nullptr;
    }
    ObjectPtr value = Eval(pair.second, environment);
    HashKey hash_key = Hash(key);
    result->Set(hash_key, HashPair(key, value));
  }

  return result;
}

ObjectPtr Evaluator::EvalHashIndexExpression(ObjectPtr hash, ObjectPtr index)
{
  HashObjectPtr object = std::dynamic_pointer_cast<HashObject>(hash);
  if (!index->hashable)
  {
    std::cout << "evaluator error: key " << index->Inspect() << " is not hashable" << std::endl;
    return nullptr;
  }

  HashKey hash_key = Hash(index);

  if (object->pairs.find(hash_key) != object->pairs.end())
  {
    HashPair &hash_pair = object->pairs[Hash(index)];
    return hash_pair.value;
  }
  else
  {
    return std::make_shared<NullObject>();
  }
}

ObjectPtr Evaluator::EvalSetLiteral(NodePtr node, EnvironmentPtr environment)
{
  SetLiteralNodePtr set_node = std::dynamic_pointer_cast<SetLiteralNode>(node);
  return std::make_shared<SetObject>(EvalExpressions(set_node->elements, environment));
}

ObjectPtr Evaluator::EvalTuple(NodePtr node, EnvironmentPtr environment)
{
  TupleNodePtr tuple_node = std::dynamic_pointer_cast<TupleNode>(node);
  return std::make_shared<TupleObject>(EvalExpressions(tuple_node->elements, environment));
}

ObjectPtr Evaluator::EvalTupleIndexExpression(ObjectPtr array, ObjectPtr index)
{
  TupleObjectPtr tuple_object = std::dynamic_pointer_cast<TupleObject>(array);
  std::vector<ObjectPtr> &elements = tuple_object->elements;
  int tuple_size = static_cast<int>(elements.size());

  IntegerObjectPtr tuple_index = std::dynamic_pointer_cast<IntegerObject>(index);
  int64_t index_value = tuple_index->value;

  if (index_value >= tuple_size)
  {
    std::cout << "error: tuple index out of range" << std::endl;
    return std::make_shared<NullObject>();
  }
  else if (index_value < 0)
  {
    std::cout << "error: tuple index cannot be negative" << std::endl;
    return std::make_shared<NullObject>();
  }
  return elements[static_cast<size_t>(index_value)];
}

ObjectPtr Evaluator::EvalKeyValueArgument(NodePtr node, EnvironmentPtr environment)
{
  KeyValueArgumentNodePtr kvpair = std::dynamic_pointer_cast<KeyValueArgumentNode>(node);
  KeyValueArgumentObjectPtr result =
      std::make_shared<KeyValueArgumentObject>(kvpair->key, Eval(kvpair->value, environment));
  return result;
}

} // namespace walnut