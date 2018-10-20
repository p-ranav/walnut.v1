#include <parser.hpp>
#include <algorithm>

Parser::Parser(TokenVectorConstRef tokens) : current_token(Token()),
                                             peek_token(Token()),
                                             current_token_index(0),
                                             statements({}),
                                             tokens(tokens),
                                             precedences({
                                                 {TokenType::LOGICAL_AND_OPERATOR, LOGICAL_AND},
                                                 {TokenType::LOGICAL_OR_OPERATOR, LOGICAL_OR},
                                                 {TokenType::LEFT_PARENTHESIS, CALL},
                                                 {TokenType::EQUALITY_OPERATOR, EQUAL},
                                                 {TokenType::INEQUALITY_OPERATOR, EQUAL},
                                                 {TokenType::LESSER_THAN_OPERATOR, LESSGREATER},
                                                 {TokenType::LESSER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
                                                 {TokenType::GREATER_THAN_OPERATOR, LESSGREATER},
                                                 {TokenType::GREATER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
                                                 {TokenType::ADDITION_OPERATOR, SUM},
                                                 {TokenType::SUBTRACTION_OPERATOR, SUM},
                                                 {TokenType::MULTIPLICATION_OPERATOR, PRODUCT},
                                                 {TokenType::DIVISION_OPERATOR, PRODUCT},
                                                 {TokenType::MODULUS_OPERATOR, PRODUCT},
                                                 {TokenType::LEFT_SQUARE_BRACKETS, INDEX},
                                                 {TokenType::DOT_OPERATOR, DOT}
                                             })
{
  // prefix parse functions
  RegisterPrefixParseFunction(TokenType::SYMBOL, std::bind(&Parser::ParseIdentifier, this));
  RegisterPrefixParseFunction(TokenType::INTEGER, std::bind(&Parser::ParseInteger, this));
  RegisterPrefixParseFunction(TokenType::DOUBLE, std::bind(&Parser::ParseDouble, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_TRUE, std::bind(&Parser::ParseBoolean, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_FALSE, std::bind(&Parser::ParseBoolean, this));
  RegisterPrefixParseFunction(TokenType::STRING_LITERAL, std::bind(&Parser::ParseStringLiteral, this));
  RegisterPrefixParseFunction(TokenType::SUBTRACTION_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));
  RegisterPrefixParseFunction(TokenType::LOGICAL_NOT_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));
  RegisterPrefixParseFunction(TokenType::LEFT_PARENTHESIS, std::bind(&Parser::ParseGroupedExpression, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_IF, std::bind(&Parser::ParseIfExpression, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_WHILE, std::bind(&Parser::ParseWhileExpression, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_FOR, std::bind(&Parser::ParseForExpression, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_VAR, std::bind(&Parser::ParseVarStatement, this));
  RegisterPrefixParseFunction(TokenType::KEYWORD_FUNCTION, std::bind(&Parser::ParseFunctionLiteral, this));
  RegisterPrefixParseFunction(TokenType::LEFT_CURLY_BRACES, std::bind(&Parser::ParseBlockStatement, this));
  RegisterPrefixParseFunction(TokenType::LEFT_SQUARE_BRACKETS, std::bind(&Parser::ParseArrayLiteral, this));

  // infix parse functions
  RegisterInfixParseFunction(TokenType::ADDITION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::SUBTRACTION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::MULTIPLICATION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::DIVISION_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::MODULUS_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::EQUALITY_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::INEQUALITY_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LESSER_THAN_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LESSER_THAN_OR_EQUAL_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::GREATER_THAN_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::GREATER_THAN_OR_EQUAL_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LOGICAL_AND_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LOGICAL_OR_OPERATOR, std::bind(&Parser::ParseInfixExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LEFT_PARENTHESIS, std::bind(&Parser::ParseCallExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::LEFT_SQUARE_BRACKETS, std::bind(&Parser::ParseIndexExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(TokenType::DOT_OPERATOR, std::bind(&Parser::ParseDotOperator, this, std::placeholders::_1));
}

void Parser::ParseProgram()
{
  NextToken();
  NextToken();

  while (!IsPeekToken(TokenType::END_OF_FILE))
  {
    NodePtr statement = ParseStatement();
    if (statement != nullptr)
      statements.push_back(statement);
    NextToken();
  }
}

void Parser::NextToken()
{
  current_token = peek_token;
  current_token_index += 1;
  peek_token = Token("", 1, 1, TokenType::END_OF_FILE, "");
  if (current_token_index - 1 < tokens.size())
    peek_token = tokens[current_token_index - 1];
}

bool Parser::IsCurrentToken(TokenType value)
{
  return (current_token.type == value);
}

bool Parser::IsCurrentTokenInList(const std::vector<TokenType>& value)
{
  return (std::find(value.begin(), value.end(), current_token.type) != value.end());
}

bool Parser::IsPeekToken(TokenType value)
{
  return (peek_token.type == value);
}

bool Parser::IsPeekTokenInList(const std::vector<TokenType>& value)
{
  return (std::find(value.begin(), value.end(), peek_token.type) != value.end());
}

bool Parser::ExpectPeek(TokenType value)
{
  if (IsPeekToken(value))
  {
    NextToken();
    return true;
  }
  else {
    String message;
    if (current_token.file != "")
      message = "parser error: unexpected token \"" + current_token.value + "\" at "
      + current_token.file + ", line " + std::to_string(current_token.line) + " char "
      + std::to_string(current_token.cursor);
    else
      message = "parser error: unexpected token \"" + current_token.value + "\"";
    std::cout << message << std::endl;
    return false;
  }
}

NodePtr Parser::ParseStatement()
{
  switch (current_token.type)
  {
  case TokenType::KEYWORD_VAR:
    return ParseVarStatement();
    break;
  case TokenType::KEYWORD_RETURN:
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

  if (!ExpectPeek(TokenType::SYMBOL))
  {
    return nullptr;
  }
  result->name = std::make_shared<IdentifierNode>(current_token.value);

  if (!ExpectPeek(TokenType::ASSIGNMENT_OPERATOR))
  {
    result->expression = nullptr;
  }
  else
  {
    NextToken();
    result->expression = ParseExpression(LOWEST);
  }

  if (IsPeekToken(TokenType::SEMI_COLON_OPERATOR) || IsPeekToken(TokenType::COMMA_OPERATOR))
    NextToken();

  return result;
}

NodePtr Parser::ParseReturnStatement()
{
  ReturnStatementNodePtr result = std::make_shared<ReturnStatementNode>();
  NextToken();

  result->expression = ParseExpression(LOWEST);

  if (IsPeekToken(TokenType::SEMI_COLON_OPERATOR))
    NextToken();

  return result;
}

void Parser::RegisterPrefixParseFunction(TokenType token_type, PrefixParseFunction function)
{
  if (prefix_parse_functions.find(token_type) != prefix_parse_functions.end())
    prefix_parse_functions[token_type] = function;
  else
    prefix_parse_functions.insert(PrefixParseFunctionMap::value_type(token_type, function));
}

void Parser::RegisterInfixParseFunction(TokenType token_type, InfixParseFunction function)
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
  if (IsPeekToken(TokenType::SEMI_COLON_OPERATOR))
    NextToken();

  return result;
}

NodePtr Parser::ParseExpression(Precedence precedence, std::vector<TokenType> end)
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

    if (IsCurrentTokenInList(end))
      break;

    NextToken();
    left_expression = infix(left_expression);

    if (IsCurrentTokenInList(end))
      break;
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
  return std::make_shared<BooleanNode>(current_token.type == TokenType::KEYWORD_TRUE);
}

NodePtr Parser::ParseStringLiteral()
{
  StringLiteralNodePtr result = std::make_shared<StringLiteralNode>(current_token.value);
  while (IsPeekToken(TokenType::SEMI_COLON_OPERATOR))
    NextToken();
  return result;
}

NodePtr Parser::ParsePrefixExpression()
{
  PrefixExpressionNodePtr result = std::make_shared<PrefixExpressionNode>(current_token.type);
  TokenType prefix_operator = current_token.type;
  NextToken();
  if (prefix_operator == TokenType::LOGICAL_NOT_OPERATOR)
    result->right = ParseExpression(PREFIX);
  else
    result->right = ParseExpression(LOWEST);
  return result;
}

NodePtr Parser::ParseGroupedExpression()
{
  NextToken();
  NodePtr result = ParseExpression(LOWEST);
  if (!ExpectPeek(TokenType::RIGHT_PARENTHESIS))
    return nullptr;
  return result;
}

BlockStatementNodePtr Parser::ParseBlockStatement()
{
  BlockStatementNodePtr result = std::make_shared<BlockStatementNode>();
  NextToken();

  while (!IsCurrentToken(TokenType::RIGHT_CURLY_BRACES) && !IsCurrentToken(TokenType::END_OF_FILE))
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

  if (IsPeekToken(TokenType::LEFT_PARENTHESIS))
    NextToken();

  NextToken();

  result->condition = ParseExpression(LOWEST);

  if (IsPeekToken(TokenType::RIGHT_PARENTHESIS))
    NextToken();

  if (!ExpectPeek(TokenType::LEFT_CURLY_BRACES))
    return nullptr;

  result->consequence = ParseBlockStatement();

  if (IsPeekToken(TokenType::KEYWORD_ELSE))
  {
    NextToken();
    if (!ExpectPeek(TokenType::LEFT_CURLY_BRACES))
      return nullptr;

    result->alternative = ParseBlockStatement();
  }

  return result;
}

NodePtr Parser::ParseWhileExpression()
{
  WhileExpressionNodePtr result = std::make_shared<WhileExpressionNode>();

  NextToken();

  if (IsCurrentToken(TokenType::LEFT_CURLY_BRACES)) 
  {
    NextToken();
    result->condition = std::make_shared<BooleanNode>(true);
  }
  else
  {
    result->condition = ParseExpression(LOWEST);

    if (!ExpectPeek(TokenType::LEFT_CURLY_BRACES))
      return nullptr;
  }

  result->consequence = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseForExpression()
{
  ForExpressionNodePtr result = std::make_shared<ForExpressionNode>();
  NextToken();

  NodePtr iterator = ParseExpression(LOWEST, { TokenType::COMMA_OPERATOR });
  if (iterator)
    result->iterators.push_back(iterator);

  while (IsPeekToken(TokenType::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    NodePtr iterator = ParseExpression(LOWEST, { TokenType::COMMA_OPERATOR, TokenType::KEYWORD_IN });
    if (iterator)
      result->iterators.push_back(iterator);
  }

  if (!ExpectPeek(TokenType::KEYWORD_IN))
  {
    return nullptr;
  }

  NextToken();
  result->iterable = ParseExpression(LOWEST, { TokenType::LEFT_CURLY_BRACES });

  if (!ExpectPeek(TokenType::LEFT_CURLY_BRACES))
  {
    return nullptr;
  }

  result->body = ParseBlockStatement();

  return result;
}

std::vector<IdentifierNodePtr> Parser::ParseFunctionParameters()
{
  std::vector<IdentifierNodePtr> result = {};

  if (IsPeekToken(TokenType::RIGHT_PARENTHESIS))
  {
    NextToken();
    return result;
  }

  NextToken();

  IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token.value);
  result.push_back(identifier);

  while (IsPeekToken(TokenType::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token.value);
    result.push_back(identifier);
  }

  if (!ExpectPeek(TokenType::RIGHT_PARENTHESIS))
    return {};

  return result;
}

NodePtr Parser::ParseFunctionLiteral()
{
  FunctionLiteralNodePtr result = std::make_shared<FunctionLiteralNode>();

  if (!ExpectPeek(TokenType::LEFT_PARENTHESIS))
    return nullptr;

  result->parameters = ParseFunctionParameters();

  if (!ExpectPeek(TokenType::LEFT_CURLY_BRACES))
    return nullptr;

  result->body = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseCallExpression(NodePtr function)
{
  CallExpressionNodePtr result = std::make_shared<CallExpressionNode>();
  result->function = function;
  result->arguments = ParseExpressionList(TokenType::RIGHT_PARENTHESIS);
  return result;
}

NodePtr Parser::ParseInfixExpression(NodePtr left) {
  InfixExpressionNodePtr result = std::make_shared<InfixExpressionNode>(current_token.type);
  result->left = left;
  Precedence precedence = CurrentPrecedence();
  NextToken();
  result->right = ParseExpression(precedence);
  return result;
}

NodePtr Parser::ParseArrayLiteral()
{
  ArrayLiteralNodePtr array_literal = std::make_shared<ArrayLiteralNode>();
  array_literal->elements = ParseExpressionList(TokenType::RIGHT_SQUARE_BRACKETS);
  return array_literal;
}

std::vector<NodePtr> Parser::ParseExpressionList(TokenType end)
{
  std::vector<NodePtr> elements;

  if (IsPeekToken(end))
  {
    NextToken();
    return elements;
  }
  NextToken();

  elements.push_back(ParseExpression(LOWEST));

  while (IsPeekToken(TokenType::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    elements.push_back(ParseExpression(LOWEST));
  }

  if (!ExpectPeek(end))
  {
    return {};
  }

  return elements;
}

NodePtr Parser::ParseIndexExpression(NodePtr left)
{
  IndexExpressionNodePtr expression = std::make_shared<IndexExpressionNode>(left);
  NextToken();
  expression->index = ParseExpression(LOWEST);
  if (!ExpectPeek(TokenType::RIGHT_SQUARE_BRACKETS))
    return nullptr;
  return expression;
}

NodePtr Parser::ParseDotOperator(NodePtr left)
{
  NextToken();
  NodePtr right = ParseExpression(LOWEST, { TokenType::RIGHT_PARENTHESIS });
  CallExpressionNodePtr call_expression = std::dynamic_pointer_cast<CallExpressionNode>(right);
  if (call_expression != nullptr)
    call_expression->arguments.insert(call_expression->arguments.begin(), left);
  return call_expression;
}