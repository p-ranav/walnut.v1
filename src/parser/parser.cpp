#include <parser.hpp>

Parser::Parser(TokenVectorConstRef tokens) : current_token(Token()),
                                             peek_token(Token()),
                                             current_token_index(0),
                                             statements({}),
                                             tokens(tokens),
                                             precedences({
                                                 {TokenType::LEFT_PARANTHESIS, CALL},
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
                                             })
{
  // prefix parse functions
  RegisterPrefixParseFunction(TokenType::SYMBOL, std::bind(&Parser::ParseIdentifier, this));
  RegisterPrefixParseFunction(TokenType::INTEGER, std::bind(&Parser::ParseInteger, this));
  RegisterPrefixParseFunction(TokenType::DOUBLE, std::bind(&Parser::ParseDouble, this));
  RegisterPrefixParseFunction(TokenType::SUBTRACTION_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));
  RegisterPrefixParseFunction(TokenType::LOGICAL_NOT_OPERATOR, std::bind(&Parser::ParsePrefixExpression, this));

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
}

void Parser::ParseProgram()
{
  NextToken();
  NextToken();

  while (!IsPeekToken(TokenType::END_OF_FILE))
  {
    AstNodePtr statement = ParseStatement();
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
  if (current_token_index < tokens.size())
    peek_token = tokens[current_token_index];
}

bool Parser::IsCurrentToken(TokenType value)
{
  return (current_token.type == value);
}

bool Parser::IsPeekToken(TokenType value)
{
  return (peek_token.type == value);
}

bool Parser::ExpectPeek(TokenType value)
{
  if (IsPeekToken(value))
  {
    NextToken();
    return true;
  }
  else
    throw std::runtime_error("expected token X, instead got token Y");
}

AstNodePtr Parser::ParseStatement()
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

AstNodePtr Parser::ParseVarStatement()
{
  AstVarStatementNodePtr result = std::make_shared<AstVarStatementNode>();

  if (!ExpectPeek(TokenType::SYMBOL))
  {
    return nullptr;
  }
  result->name = std::make_shared<AstIdentifierNode>(current_token.value);

  if (!ExpectPeek(TokenType::ASSIGNMENT_OPERATOR))
  {
    return nullptr;
  }

  // TODO: parse expression
  while (!IsCurrentToken(TokenType::SEMI_COLON_OPERATOR))
  {
    NextToken();
  }

  return result;
}

AstNodePtr Parser::ParseReturnStatement()
{
  AstReturnStatementNodePtr result = std::make_shared<AstReturnStatementNode>();
  NextToken();

  while (!IsCurrentToken(TokenType::SEMI_COLON_OPERATOR))
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

AstNodePtr Parser::ParseExpressionStatement()
{
  AstNodePtr result = ParseExpression(LOWEST);

  if (IsPeekToken(TokenType::SEMI_COLON_OPERATOR))
    NextToken();

  return result;
}

AstNodePtr Parser::ParseExpression(Precedence precedence)
{
  PrefixParseFunction prefix = prefix_parse_functions[current_token.type];

  if (prefix == nullptr)
    return nullptr;

  AstNodePtr left_expression = prefix();

  while (!IsPeekToken(TokenType::SEMI_COLON_OPERATOR) && precedence < PeekPrecedence())
  {
    InfixParseFunction infix = infix_parse_functions[peek_token.type];

    if (infix == nullptr)
      return left_expression;

    NextToken();
    left_expression = infix(left_expression);
  }

  return left_expression;
}

AstNodePtr Parser::ParseIdentifier()
{
  return std::make_shared<AstIdentifierNode>(current_token.value);
}

AstNodePtr Parser::ParseInteger()
{
  return std::make_shared<AstIntegerNode>(std::stoi(current_token.value));
}

AstNodePtr Parser::ParseDouble()
{
  return std::make_shared<AstDoubleNode>(std::stod(current_token.value));
}

AstNodePtr Parser::ParsePrefixExpression()
{
  AstPrefixExpressionNodePtr result = std::make_shared<AstPrefixExpressionNode>(current_token.type);
  NextToken();
  result->right = ParseExpression(LOWEST);
  return result;
}

AstNodePtr Parser::ParseInfixExpression(AstNodePtr left) {
  AstInfixExpressionNodePtr result = std::make_shared<AstInfixExpressionNode>(current_token.type);
  result->left = left;
  NextToken();
  result->right = ParseExpression(CurrentPrecedence());
  return result;
}