#include <parser.hpp>
#include <algorithm>

Parser::Parser(TokenVectorConstRef tokens) : current_token(Token()),
                                             peek_token(Token()),
                                             current_token_index(0),
                                             statements({}),
                                             tokens(tokens),
                                             precedences({
                                                 {Token::Type::LOGICAL_AND_OPERATOR, LOGICAL_AND},
                                                 {Token::Type::LOGICAL_OR_OPERATOR, LOGICAL_OR},
                                                 {Token::Type::LEFT_PARENTHESIS, CALL},
                                                 {Token::Type::EQUALITY_OPERATOR, EQUAL},
                                                 {Token::Type::INEQUALITY_OPERATOR, EQUAL},
                                                 {Token::Type::LESSER_THAN_OPERATOR, LESSGREATER},
                                                 {Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
                                                 {Token::Type::GREATER_THAN_OPERATOR, LESSGREATER},
                                                 {Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
                                                 {Token::Type::ADDITION_OPERATOR, SUM},
                                                 {Token::Type::SUBTRACTION_OPERATOR, SUM},
                                                 {Token::Type::MULTIPLICATION_OPERATOR, PRODUCT},
                                                 {Token::Type::DIVISION_OPERATOR, PRODUCT},
                                                 {Token::Type::MODULUS_OPERATOR, PRODUCT},
                                                 {Token::Type::LEFT_SQUARE_BRACKETS, INDEX},
                                                 {Token::Type::DOT_OPERATOR, DOT}
                                             })
{
  // prefix parse functions
  RegisterPrefixParseFunction(Token::Type::SYMBOL, std::bind(&Parser::ParseIdentifier, this));
  RegisterPrefixParseFunction(Token::Type::INTEGER, std::bind(&Parser::ParseInteger, this));
  RegisterPrefixParseFunction(Token::Type::DOUBLE, std::bind(&Parser::ParseDouble, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_TRUE, std::bind(&Parser::ParseBoolean, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_FALSE, std::bind(&Parser::ParseBoolean, this));
  RegisterPrefixParseFunction(Token::Type::CHARACTER, std::bind(&Parser::ParseCharacter, this));
  RegisterPrefixParseFunction(Token::Type::STRING_LITERAL, std::bind(&Parser::ParseStringLiteral, this));
  RegisterPrefixParseFunction(Token::Type::SUBTRACTION_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));
  RegisterPrefixParseFunction(Token::Type::LOGICAL_NOT_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));
  RegisterPrefixParseFunction(Token::Type::LEFT_PARENTHESIS, std::bind(&Parser::ParseGroupedExpression, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_IF, std::bind(&Parser::ParseIfExpression, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_WHILE, std::bind(&Parser::ParseWhileExpression, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_FOR, std::bind(&Parser::ParseForExpression, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_VAR, std::bind(&Parser::ParseVarStatement, this));
  RegisterPrefixParseFunction(Token::Type::KEYWORD_FUNCTION, std::bind(&Parser::ParseFunctionLiteral, this));
  RegisterPrefixParseFunction(Token::Type::LEFT_CURLY_BRACES, std::bind(&Parser::ParseBlockStatement, this));
  RegisterPrefixParseFunction(Token::Type::LEFT_SQUARE_BRACKETS, std::bind(&Parser::ParseArrayLiteral, this));

  // infix parse functions
  RegisterInfixParseFunction(Token::Type::ADDITION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::SUBTRACTION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::MULTIPLICATION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::DIVISION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::MODULUS_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::EQUALITY_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::INEQUALITY_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LESSER_THAN_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::GREATER_THAN_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LOGICAL_AND_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LOGICAL_OR_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LEFT_PARENTHESIS, std::bind(&Parser::ParseCallExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::LEFT_SQUARE_BRACKETS, std::bind(&Parser::ParseIndexExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::DOT_OPERATOR, std::bind(&Parser::ParseDotOperator, this, std::placeholders::_1));
}

void Parser::ParseProgram()
{
  NextToken();
  NextToken();

  while (!IsPeekToken(Token::Type::END_OF_FILE))
  {
    NodePtr statement = ParseStatement();
    if (statement != nullptr)
    {
      statements.push_back(statement);
      // std::cout << "[STATEMENT] " << statement->ToString() << std::endl;
    }
    NextToken();
  }
}

void Parser::NextToken()
{
  current_token = peek_token;
  current_token_index += 1;
  peek_token = Token("", 1, 1, Token::Type::END_OF_FILE, "");
  if (current_token_index - 1 < tokens.size())
    peek_token = tokens[current_token_index - 1];
}

bool Parser::IsCurrentToken(Token::Type value)
{
  return (current_token.type == value);
}

bool Parser::IsCurrentTokenInList(const std::vector<Token::Type>& value)
{
  return (std::find(value.begin(), value.end(), current_token.type) != value.end());
}

bool Parser::IsPeekToken(Token::Type value)
{
  return (peek_token.type == value);
}

bool Parser::IsPeekTokenInList(const std::vector<Token::Type>& value)
{
  return (std::find(value.begin(), value.end(), peek_token.type) != value.end());
}

bool Parser::ExpectPeek(Token::Type value)
{
  if (IsPeekToken(value))
  {
    NextToken();
    return true;
  }
  else {
    String message;
    if (peek_token.file != "")
      message = "parser error: unexpected token \"" + peek_token.value + "\" at "
      + peek_token.file + ", line " + std::to_string(peek_token.line) + " char "
      + std::to_string(peek_token.cursor) + ", expected \"" + TokenString(value) + "\"";
    else
      message = "parser error: unexpected token \"" + peek_token.value + "\"";
    std::cout << message << std::endl;
    return false;
  }
}

NodePtr Parser::ParseStatement()
{
  switch (current_token.type)
  {
  case Token::Type::KEYWORD_VAR:
    return ParseVarStatement();
    break;
  case Token::Type::KEYWORD_RETURN:
    return ParseReturnStatement();
    break;
  default:
    return ParseExpressionStatement();
    break;
  }
}

NodePtr Parser::ParseVarStatement()
{
  VarStatementNodePtr result = std::make_shared<VarStatementNode>();

  if (!ExpectPeek(Token::Type::SYMBOL))
  {
    return nullptr;
  }
  result->name = std::make_shared<IdentifierNode>(current_token.value);

  if (!ExpectPeek(Token::Type::ASSIGNMENT_OPERATOR))
  {
    result->expression = nullptr;
  }
  else
  {
    NextToken();
    result->expression = ParseExpression(LOWEST);
  }

  if (IsPeekToken(Token::Type::SEMI_COLON_OPERATOR) || IsPeekToken(Token::Type::COMMA_OPERATOR))
    NextToken();

  return result;
}

NodePtr Parser::ParseReturnStatement()
{
  ReturnStatementNodePtr result = std::make_shared<ReturnStatementNode>();
  NextToken();

  result->expression = ParseExpression(LOWEST);

  return result;
}

void Parser::RegisterPrefixParseFunction(Token::Type token_type, PrefixParseFunction function)
{
  if (prefix_parse_functions.find(token_type) != prefix_parse_functions.end())
    prefix_parse_functions[token_type] = function;
  else
    prefix_parse_functions.insert(PrefixParseFunctionMap::value_type(token_type, function));
}

void Parser::RegisterInfixParseFunction(Token::Type token_type, InfixParseFunction function)
{
  if (infix_parse_functions.find(token_type) != infix_parse_functions.end())
    infix_parse_functions[token_type] = function;
  else
    infix_parse_functions.insert(InfixParseFunctionMap::value_type(token_type, function));
}

Parser::Precedence Parser::PeekPrecedence()
{
  if (precedences.find(peek_token.type) != precedences.end())
    return precedences[peek_token.type];
  else
    return LOWEST;
}

Parser::Precedence Parser::CurrentPrecedence()
{
  if (precedences.find(current_token.type) != precedences.end())
    return precedences[current_token.type];
  else
    return LOWEST;
}

NodePtr Parser::ParseExpressionStatement()
{
  NodePtr result = ParseExpression(LOWEST);

  if (IsPeekToken(Token::Type::ASSIGNMENT_OPERATOR))
  {
    ExpressionAssignmentStatementNodePtr statement = std::make_shared<ExpressionAssignmentStatementNode>();
    statement->left = result;
    NextToken();
    NextToken();
    statement->expression = ParseExpression(LOWEST);
    result = statement;
  }

  if (IsPeekToken(Token::Type::SEMI_COLON_OPERATOR) || IsPeekToken(Token::Type::END_OF_FILE))
    NextToken();

  return result;
}

NodePtr Parser::ParseExpression(Precedence precedence, std::vector<Token::Type> end)
{
  PrefixParseFunction prefix = prefix_parse_functions[current_token.type];

  if (prefix == nullptr)
    return nullptr;

  NodePtr left_expression = prefix();

  while (!IsPeekTokenInList(end) && precedence < PeekPrecedence())
  {
    InfixParseFunction infix = infix_parse_functions[peek_token.type];

    if (infix == nullptr)
      return left_expression;

    NextToken();
    left_expression = infix(left_expression);
  }

  return left_expression;
}

NodePtr Parser::ParseIdentifier()
{
  return std::make_shared<IdentifierNode>(current_token.value);
}

NodePtr Parser::ParseInteger()
{
  return std::make_shared<IntegerNode>(std::stoi(current_token.value));
}

NodePtr Parser::ParseDouble()
{
  return std::make_shared<DoubleNode>(std::stod(current_token.value));
}

NodePtr Parser::ParseBoolean()
{
  return std::make_shared<BooleanNode>(current_token.type == Token::Type::KEYWORD_TRUE);
}

NodePtr Parser::ParseCharacter()
{
  CharacterNodePtr result = std::make_shared<CharacterNode>(current_token.value);
  while (IsPeekToken(Token::Type::SEMI_COLON_OPERATOR))
    NextToken();
  return result;
}

NodePtr Parser::ParseStringLiteral()
{
  StringLiteralNodePtr result = std::make_shared<StringLiteralNode>(current_token.value);
  while (IsPeekToken(Token::Type::SEMI_COLON_OPERATOR))
    NextToken();
  return result;
}

NodePtr Parser::ParsePrefixExpression()
{
  PrefixExpressionNodePtr result = std::make_shared<PrefixExpressionNode>(current_token.type);
  Token::Type prefix_operator = current_token.type;
  NextToken();
  if (prefix_operator == Token::Type::LOGICAL_NOT_OPERATOR)
    result->right = ParseExpression(PREFIX);
  else
    result->right = ParseExpression(LOWEST);
  return result;
}

NodePtr Parser::ParseGroupedExpression()
{
  NextToken();
  NodePtr result = ParseExpression(LOWEST);
  if (!ExpectPeek(Token::Type::RIGHT_PARENTHESIS))
    return nullptr;
  return result;
}

BlockStatementNodePtr Parser::ParseBlockStatement()
{
  BlockStatementNodePtr result = std::make_shared<BlockStatementNode>();
  NextToken();

  while (!IsCurrentToken(Token::Type::RIGHT_CURLY_BRACES) && !IsCurrentToken(Token::Type::END_OF_FILE))
  {
    NodePtr statement = ParseStatement();
    if (statement != nullptr)
      result->statements.push_back(statement);
    NextToken();
  }
  return result;
}

NodePtr Parser::ParseIfExpression()
{
  IfExpressionNodePtr result = std::make_shared<IfExpressionNode>();
  NextToken();

  result->condition = ParseExpression(LOWEST);

  if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    return nullptr;

  result->consequence = ParseBlockStatement();

  if (IsPeekToken(Token::Type::KEYWORD_ELSE))
  {
    NextToken();
    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
      return nullptr;

    result->alternative = ParseBlockStatement();
  }

  return result;
}

NodePtr Parser::ParseWhileExpression()
{
  WhileExpressionNodePtr result = std::make_shared<WhileExpressionNode>();

  NextToken();

  if (IsCurrentToken(Token::Type::LEFT_CURLY_BRACES)) 
  {
    NextToken();
    result->condition = std::make_shared<BooleanNode>(true);
  }
  else
  {
    result->condition = ParseExpression(LOWEST, { Token::Type::LEFT_CURLY_BRACES });

    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
      return nullptr;
  }

  result->consequence = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseForExpression()
{
  ForExpressionNodePtr result = std::make_shared<ForExpressionNode>();
  NextToken();

  NodePtr iterator = ParseExpression(LOWEST, { Token::Type::COMMA_OPERATOR });
  if (iterator)
    result->iterators.push_back(iterator);

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    NodePtr iterator = ParseExpression(LOWEST, { Token::Type::COMMA_OPERATOR, Token::Type::KEYWORD_IN });
    if (iterator)
      result->iterators.push_back(iterator);
  }

  if (!ExpectPeek(Token::Type::KEYWORD_IN))
    return nullptr;

  NextToken();
  result->iterable = ParseExpression(LOWEST, { Token::Type::LEFT_CURLY_BRACES });

  if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    return nullptr;

  result->body = ParseBlockStatement();

  return result;
}

std::vector<IdentifierNodePtr> Parser::ParseFunctionParameters()
{
  std::vector<IdentifierNodePtr> result = {};

  if (IsPeekToken(Token::Type::RIGHT_PARENTHESIS))
  {
    NextToken();
    return result;
  }

  NextToken();

  IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token.value);
  result.push_back(identifier);

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token.value);
    result.push_back(identifier);
  }

  if (!ExpectPeek(Token::Type::RIGHT_PARENTHESIS))
    return {};

  return result;
}

NodePtr Parser::ParseFunctionLiteral()
{
  FunctionLiteralNodePtr result = std::make_shared<FunctionLiteralNode>();

  if (!ExpectPeek(Token::Type::LEFT_PARENTHESIS))
    return nullptr;

  result->parameters = ParseFunctionParameters();

  if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    return nullptr;

  result->body = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseCallExpression(NodePtr function)
{
  CallExpressionNodePtr result = std::make_shared<CallExpressionNode>();
  result->function = function;
  result->arguments = ParseExpressionList(Token::Type::RIGHT_PARENTHESIS);
  return result;
}

NodePtr Parser::ParseInfixExpression(NodePtr left) {
  InfixExpressionNodePtr result = std::make_shared<InfixExpressionNode>(current_token.type);
  result->left = left;
  Precedence precedence = CurrentPrecedence();
  NextToken();
  result->right = ParseExpression(precedence, 
    { Token::Type::SEMI_COLON_OPERATOR, Token::Type::END_OF_FILE, Token::Type::RIGHT_PARENTHESIS });
  return result;
}

NodePtr Parser::ParseArrayLiteral()
{
  ArrayLiteralNodePtr array_literal = std::make_shared<ArrayLiteralNode>();
  array_literal->elements = ParseExpressionList(Token::Type::RIGHT_SQUARE_BRACKETS);
  return array_literal;
}

std::vector<NodePtr> Parser::ParseExpressionList(Token::Type end)
{
  std::vector<NodePtr> elements;

  if (IsPeekToken(end))
  {
    NextToken();
    return elements;
  }
  NextToken();

  elements.push_back(ParseExpression(LOWEST, {Token::Type::SEMI_COLON_OPERATOR, Token::Type::RIGHT_PARENTHESIS}));

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    elements.push_back(ParseExpression(LOWEST));
  }

  if (!ExpectPeek(end))
    return {};

  return elements;
}

NodePtr Parser::ParseIndexExpression(NodePtr left)
{
  IndexExpressionNodePtr expression = std::make_shared<IndexExpressionNode>(left);
  NextToken();
  expression->index = ParseExpression(LOWEST);
  if (!ExpectPeek(Token::Type::RIGHT_SQUARE_BRACKETS))
    return nullptr;
  return expression;
}

NodePtr Parser::ParseDotOperator(NodePtr left)
{
  NextToken();
  NodePtr right = ParseExpression(SUM, {
    Token::Type::SEMI_COLON_OPERATOR, Token::Type::RIGHT_PARENTHESIS, Token::Type::DOT_OPERATOR });
  CallExpressionNodePtr call_expression = std::dynamic_pointer_cast<CallExpressionNode>(right);
  if (call_expression != nullptr)
    call_expression->arguments.insert(call_expression->arguments.begin(), left);
  return call_expression;
}