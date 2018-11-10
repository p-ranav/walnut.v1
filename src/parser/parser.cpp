#include <parser.hpp>
#include <algorithm>

namespace walnut
{

Parser::Parser(TokenVectorConstRef tokens, StringConstRef buffer) : current_token(Token()),
                                                                    buffer(buffer),
                                                                    peek_token(Token()),
                                                                    current_token_index(0),
                                                                    statements({}),
                                                                    tokens(tokens),
                                                                    precedences({
                                                                        // If-else
                                                                        {Token::Type::KEYWORD_IF, IF_ELSE},
                                                                        // Logical AND
                                                                        {Token::Type::LOGICAL_AND_OPERATOR, LOGICAL_AND},
                                                                        // Logical OR
                                                                        {Token::Type::LOGICAL_OR_OPERATOR, LOGICAL_OR},
                                                                        // Logical NOT
                                                                        {Token::Type::LOGICAL_NOT_OPERATOR, LOGICAL_NOT},
                                                                        // Comparison
                                                                        {Token::Type::EQUALITY_OPERATOR, EQUALITY},
                                                                        {Token::Type::INEQUALITY_OPERATOR, EQUALITY},
                                                                        {Token::Type::KEYWORD_IN, COMPARISON},
                                                                        {Token::Type::KEYWORD_NOT_IN, COMPARISON},
                                                                        {Token::Type::LESSER_THAN_OPERATOR, COMPARISON},
                                                                        {Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR, COMPARISON},
                                                                        {Token::Type::GREATER_THAN_OPERATOR, COMPARISON},
                                                                        {Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR, COMPARISON},
                                                                        // Addition/Subtraction
                                                                        {Token::Type::ADDITION_OPERATOR, ADDITION_SUBTRACTION},
                                                                        {Token::Type::SUBTRACTION_OPERATOR, ADDITION_SUBTRACTION},
                                                                        // Multiplication/Division
                                                                        {Token::Type::MULTIPLICATION_OPERATOR, MULTIPLICATION_DIVISION},
                                                                        {Token::Type::DIVISION_OPERATOR, MULTIPLICATION_DIVISION},
                                                                        {Token::Type::MODULUS_OPERATOR, MULTIPLICATION_DIVISION},
                                                                        // Attribute
                                                                        {Token::Type::LEFT_SQUARE_BRACKETS, ATTRIBUTE},
                                                                        {Token::Type::DOT_OPERATOR, ATTRIBUTE},
                                                                        {Token::Type::LEFT_PARENTHESIS, ATTRIBUTE},
                                                                        {Token::Type::ARROW_OPERATOR, ATTRIBUTE},
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
  RegisterPrefixParseFunction(Token::Type::LEFT_CURLY_BRACES, std::bind(&Parser::ParseHashLiteral, this));
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
  RegisterInfixParseFunction(Token::Type::KEYWORD_IF, std::bind(&Parser::ParseTernaryOperator, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::ARROW_OPERATOR, std::bind(&Parser::ParseArrowOperator, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::KEYWORD_IN, std::bind(&Parser::ParseInExpression, this, std::placeholders::_1));
  RegisterInfixParseFunction(Token::Type::KEYWORD_NOT_IN, std::bind(&Parser::ParseInExpression, this, std::placeholders::_1));
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

void Parser::PreviousToken()
{
  peek_token = current_token;
  current_token_index -= 1;
  current_token = Token("", 1, 1, Token::Type::END_OF_FILE, "");
  if (current_token_index - 2 >= 0 && current_token_index - 2 < tokens.size())
    current_token = tokens[current_token_index - 2];
  else
    current_token = tokens[0];
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

bool Parser::IsCurrentTokenInList(const std::vector<Token::Type> &value)
{
  return (std::find(value.begin(), value.end(), current_token.type) != value.end());
}

bool Parser::IsPeekToken(Token::Type value)
{
  return (peek_token.type == value);
}

bool Parser::IsPeekTokenInList(const std::vector<Token::Type> &value)
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
  else
  {
    return false;
  }
}

unsigned int Parser::GetNumberOfDigits(unsigned int number)
{
  unsigned int digits = 0;
  if (number < 0)
    digits = 1;
  while (number)
  {
    number /= 10;
    digits += 1;
  }
  return digits;
}

void Parser::ReportError(Token error_token, String brief_descrition, String detailed_description)
{
  String file = error_token.file;
  unsigned int line = error_token.line;
  unsigned int cursor = error_token.cursor;

  std::vector<unsigned int> line_numbers = {};
  if (line == 1)
  {
    line_numbers = std::vector<unsigned int>{line, (line + 1)};
  }
  else
  {
    line_numbers = std::vector<unsigned int>{
        (line - 1), line, (line + 1)};
  }
  unsigned int max_line_number = *(std::max_element(line_numbers.begin(), line_numbers.end()));
  String blanks(GetNumberOfDigits(max_line_number), ' ');

  String message_leading_blanks(cursor - 1, ' ');
  String message_carets = "";

  if (peek_token.cursor > cursor)
  {
    message_carets = " " + String(peek_token.cursor - cursor - 1, '^');
  }
  else
  {
    message_carets = " " + String(1, '^');
  }

  std::vector<String> lines = split(buffer, "\n");
  String error_line = lines[line - 1];

  std::cout << "error: " << brief_descrition << std::endl;
  std::cout << blanks << "--> " << file << ":" << line << ":" << cursor << std::endl;

  if ((line - 1) > 0)
  {
    String line_leading_blanks = "";
    line_leading_blanks.insert(line_leading_blanks.begin(),
                               (GetNumberOfDigits(max_line_number) - GetNumberOfDigits(line - 1)),
                               ' ');
    std::cout << blanks << " |  " << std::endl;
    if ((line - 2) < lines.size())
      std::cout << line_leading_blanks << (line - 1) << " |  " << lines[line - 2] << std::endl;
    else
      std::cout << line_leading_blanks << (line - 1) << " |  " << std::endl;
  }

  String line_leading_blanks = "";
  line_leading_blanks.insert(line_leading_blanks.begin(),
                             (GetNumberOfDigits(max_line_number) - GetNumberOfDigits(line)), ' ');

  std::cout << blanks << " |  " << std::endl;
  std::cout << line_leading_blanks << line << " |  " << error_line << std::endl;
  std::cout << blanks << " | " << message_leading_blanks << message_carets
            << detailed_description << std::endl;

  line_leading_blanks = "";
  line_leading_blanks.insert(line_leading_blanks.begin(),
                             (GetNumberOfDigits(max_line_number) - GetNumberOfDigits(line + 1)), ' ');

  if ((line + 1) < lines.size())
    std::cout << line_leading_blanks << (line + 1) << " |  " << lines[line] << std::endl;
  else
    std::cout << line_leading_blanks << (line + 1) << " |  " << std::endl;

  std::cout << blanks << " |  " << std::endl;
  std::cout << std::endl;
}

NodePtr Parser::ParseStatement()
{
  switch (current_token.type)
  {
  case Token::Type::KEYWORD_VAR:
    return ParseVarStatement();
    break;
  case Token::Type::KEYWORD_ASSIGN:
    return ParseAssignmentStatement();
    break;
  case Token::Type::KEYWORD_RETURN:
    return ParseReturnStatement();
    break;
  case Token::Type::KEYWORD_IMPORT:
    return ParseImportStatement();
    break;
  default:
    return ParseExpressionStatement();
    break;
  }
}

NodePtr Parser::ParseVarStatement()
{
  VarStatementNodePtr result = std::make_shared<VarStatementNode>(current_token);
  result->statement_type = VarStatementNode::StatementType::INITIALIZATION;

  if (!ExpectPeek(Token::Type::SYMBOL))
  {
    String brief_description = "failed to parse variable initialization statement";
    String detailed_description =
        " LHS of initialization operator needs to be an identifier";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }
  result->name = std::make_shared<IdentifierNode>(current_token, current_token.value);

  if (!ExpectPeek(Token::Type::INITIALIZATION_OPERATOR))
  {
    String brief_description = "failed to parse variable initialization statement";
    String detailed_description =
        " expected the assignment operator '=' here";
    ReportError(peek_token, brief_description, detailed_description);
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

NodePtr Parser::ParseAssignmentStatement()
{
  VarStatementNodePtr result = std::make_shared<VarStatementNode>(current_token);
  result->statement_type = VarStatementNode::StatementType::ASSIGNMENT;

  if (!ExpectPeek(Token::Type::SYMBOL))
  {
    String brief_description = "failed to parse variable assignment statement";
    String detailed_description =
      " LHS of assignment operator needs to be an identifier";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }
  result->name = std::make_shared<IdentifierNode>(current_token, current_token.value);

  if (!ExpectPeek(Token::Type::ASSIGNMENT_OPERATOR))
  {
    String brief_description = "failed to parse variable assignment statement";
    String detailed_description =
      " expected the assignment operator '=' here";
    ReportError(peek_token, brief_description, detailed_description);
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
  ReturnStatementNodePtr result = std::make_shared<ReturnStatementNode>(current_token);
  NextToken();
  result->expression = ParseExpression(LOWEST);
  return result;
}

NodePtr Parser::ParseImportStatement()
{
  ImportStatementNodePtr result = std::make_shared<ImportStatementNode>(current_token, "");
  if (!ExpectPeek(Token::Type::STRING_LITERAL))
  {
    String brief_description = "expected string literal in import statement";
    String detailed_description =
        " this filename must be provided as a string literal, e.g., import \"logging.txt\"";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }

  result->value = current_token.value;

  if (!ExpectPeek(Token::Type::SEMI_COLON_OPERATOR))
  {
    String brief_description = "failed to parse import statement";
    String detailed_description = " expected a ';' here";
    ReportError(peek_token, brief_description, detailed_description);
  }
  else
  {
    NextToken();
  }
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
    ExpressionAssignmentStatementNodePtr statement = std::make_shared<ExpressionAssignmentStatementNode>(current_token);
    statement->left = result;
    NextToken();
    NextToken();
    statement->expression = ParseExpression(LOWEST);
    result = statement;
  }

  if (result != nullptr &&
    result->type != NodeType::BLOCK_STATEMENT &&
    result->type != NodeType::FOR_EXPRESSION &&
    result->type != NodeType::IF_EXPRESSION &&
    result->type != NodeType::FUNCTION &&
    result->type != NodeType::WHILE_EXPRESSION &&
    !IsPeekToken(Token::Type::RIGHT_CURLY_BRACES) &&
    !IsPeekToken(Token::Type::ASSIGNMENT_OPERATOR) &&
    !IsPeekToken(Token::Type::INITIALIZATION_OPERATOR))
  {
    if (!ExpectPeek(Token::Type::SEMI_COLON_OPERATOR))
    {
      String brief_description = "failed to parse expression statement";
      String detailed_description = " expected a ';' here";
      ReportError(peek_token, brief_description, detailed_description);
    }
  }
  else if (IsPeekToken(Token::Type::SEMI_COLON_OPERATOR) || IsPeekToken(Token::Type::END_OF_FILE))
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

    // if {...} else {...} if {...}
    // the second if should not be treated as an infix operator
    if (left_expression->type == NodeType::IF_EXPRESSION && peek_token.type == Token::Type::KEYWORD_IF)
      return left_expression;

    NextToken();
    left_expression = infix(left_expression);
  }

  return left_expression;
}

NodePtr Parser::ParseIdentifier()
{
  return std::make_shared<IdentifierNode>(current_token, current_token.value);
}

NodePtr Parser::ParseInteger()
{
  return std::make_shared<IntegerNode>(current_token, std::stoll(current_token.value));
}

NodePtr Parser::ParseDouble()
{
  return std::make_shared<DoubleNode>(current_token, std::stod(current_token.value));
}

NodePtr Parser::ParseBoolean()
{
  return std::make_shared<BooleanNode>(current_token, current_token.type == Token::Type::KEYWORD_TRUE);
}

NodePtr Parser::ParseCharacter()
{
  CharacterNodePtr result = std::make_shared<CharacterNode>(current_token, current_token.value);
  return result;
}

NodePtr Parser::ParseStringLiteral()
{
  StringLiteralNodePtr result = std::make_shared<StringLiteralNode>(current_token, current_token.value);
  return result;
}

NodePtr Parser::ParsePrefixExpression()
{
  PrefixExpressionNodePtr result = std::make_shared<PrefixExpressionNode>(current_token, current_token.type);
  Token::Type prefix_operator = current_token.type;
  NextToken();
  if (prefix_operator == Token::Type::LOGICAL_NOT_OPERATOR)
    result->right = ParseExpression(LOGICAL_NOT);
  else
    result->right = ParseExpression(LOWEST);
  return result;
}

NodePtr Parser::ParseGroupedExpression()
{
  NextToken();
  size_t start_index = current_token_index;

  if (IsCurrentToken(Token::Type::COMMA_OPERATOR))
  {
    if (!ExpectPeek(Token::Type::RIGHT_PARENTHESIS))
    {
      return nullptr;
    }
    return std::make_shared<TupleNode>(current_token);
  }

  NodePtr result = ParseExpression(LOWEST);

  if (IsPeekToken(Token::Type::COMMA_OPERATOR) ||
      // grouped expression is '()' - parse this as empty tuple
      (IsCurrentToken(Token::Type::RIGHT_PARENTHESIS) && current_token_index == start_index))
    return ParseTuple(result, start_index);

  if (!ExpectPeek(Token::Type::RIGHT_PARENTHESIS))
  {
    String brief_description = "expected ')' to terminate grouped expression";
    String detailed_description =
        " grouped expressions need to start with '(' and terminate with ')'";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }
  return result;
}

BlockStatementNodePtr Parser::ParseBlockStatement()
{
  BlockStatementNodePtr result = std::make_shared<BlockStatementNode>(current_token);
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
  IfExpressionNodePtr result = std::make_shared<IfExpressionNode>(current_token);
  NextToken();

  result->conditions.push_back(ParseExpression(LOWEST));

  if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
  {
    String brief_description = "expected '{' to mark the start of if block";
    String detailed_description =
        " the 'if' block needs to be wrapped inside curly braces: if <condition> { <consequence> }";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }

  result->consequences.push_back(ParseBlockStatement());

  while (IsPeekToken(Token::Type::KEYWORD_ELSE_IF))
  {
    NextToken();
    NextToken();
    result->conditions.push_back(ParseExpression(LOWEST));
    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    {
      String brief_description = "expected '{' to mark the start of else if block";
      String detailed_description =
          " the 'else if' block needs to be wrapped inside curly braces: else if <condition> { <consequence> }";
      ReportError(peek_token, brief_description, detailed_description);
      return nullptr;
    }

    result->consequences.push_back(ParseBlockStatement());
  }

  if (IsPeekToken(Token::Type::KEYWORD_ELSE))
  {
    NextToken();
    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    {
      String brief_description = "expected '{' to mark the start of else block";
      String detailed_description =
          " the 'else' block needs to be wrapped inside curly braces: else { <alternative> }";
      ReportError(peek_token, brief_description, detailed_description);
      return nullptr;
    }

    result->alternative = ParseBlockStatement();
  }

  return result;
}

NodePtr Parser::ParseWhileExpression()
{
  WhileExpressionNodePtr result = std::make_shared<WhileExpressionNode>(current_token);

  NextToken();

  if (IsCurrentToken(Token::Type::LEFT_CURLY_BRACES))
  {
    NextToken();
    result->condition = std::make_shared<BooleanNode>(current_token, true);
  }
  else
  {
    result->condition = ParseExpression(LOWEST, {Token::Type::LEFT_CURLY_BRACES});

    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
    {
      String brief_description = "expected '{' to mark the start of while block";
      String detailed_description =
          " the while block needs to be wrapped inside curly braces: while <condition> { <consequence> }";
      ReportError(peek_token, brief_description, detailed_description);
      return nullptr;
    }
  }

  result->consequence = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseForExpression()
{
  ForExpressionNodePtr result = std::make_shared<ForExpressionNode>(current_token);
  NextToken();

  NodePtr iterator = ParseExpression(LOWEST, {Token::Type::COMMA_OPERATOR});
  if (iterator)
    result->iterators.push_back(iterator);

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    NodePtr iterator = ParseExpression(LOWEST);
    if (iterator)
      result->iterators.push_back(iterator);
  }

  if (result->iterators.size() > 0)
  {
    if (result->iterators[result->iterators.size() - 1]->type == Node::Type::IN_EXPRESSION)
    {
      InExpressionNodePtr expression = std::dynamic_pointer_cast<InExpressionNode>(result->iterators[result->iterators.size() - 1]);
      result->iterators.pop_back();
      result->iterators.push_back(expression->iterator);
      result->iterable = expression->iterable;
    }
  }

  if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
  {
    String brief_description = "expected '{' to mark the start of for block";
    String detailed_description =
        " the for block needs to be wrapped inside curly braces: for <iterator(s)> in <iterable> { <consequence> }";
    ReportError(peek_token, brief_description, detailed_description);
    return nullptr;
  }

  result->body = ParseBlockStatement();

  return result;
}

NodePtr Parser::ParseInExpression(NodePtr left)
{
  InExpressionNodePtr expression = std::make_shared<InExpressionNode>(current_token);
  if (current_token.type == Token::Type::KEYWORD_NOT_IN)
    expression->negate_result = true;
  expression->iterator = left;
  NextToken();
  expression->iterable = ParseExpression(COMPARISON);
  return expression;
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

  IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token, current_token.value);
  result.push_back(identifier);

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    NextToken();
    IdentifierNodePtr identifier = std::make_shared<IdentifierNode>(current_token, current_token.value);
    result.push_back(identifier);
  }

  if (!ExpectPeek(Token::Type::RIGHT_PARENTHESIS))
  {
    return {};
  }

  return result;
}

NodePtr Parser::ParseFunctionLiteral()
{
  FunctionLiteralNodePtr result = std::make_shared<FunctionLiteralNode>(current_token);

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
  CallExpressionNodePtr result = std::make_shared<CallExpressionNode>(current_token);
  result->function = function;
  NodePtr expression_list = ParseExpressionList(Token::Type::RIGHT_PARENTHESIS);
  result->arguments = std::dynamic_pointer_cast<TupleNode>(expression_list);
  return result;
}

NodePtr Parser::ParseInfixExpression(NodePtr left)
{
  InfixExpressionNodePtr result = std::make_shared<InfixExpressionNode>(current_token, current_token.type);
  result->left = left;
  Precedence precedence = CurrentPrecedence();
  NextToken();
  result->right = ParseExpression(precedence,
                                  {Token::Type::SEMI_COLON_OPERATOR, Token::Type::END_OF_FILE, Token::Type::RIGHT_PARENTHESIS});
  return result;
}

NodePtr Parser::ParseArrayLiteral()
{
  ArrayLiteralNodePtr array_literal = std::make_shared<ArrayLiteralNode>(current_token);

  if (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    if (!ExpectPeek(Token::Type::RIGHT_SQUARE_BRACKETS))
    {
      return nullptr;
    }
    return array_literal;
  }

  NodePtr expression_list = ParseExpressionList(Token::Type::RIGHT_SQUARE_BRACKETS);
  TupleNodePtr expression_tuple = std::dynamic_pointer_cast<TupleNode>(expression_list);
  array_literal->elements = expression_tuple->elements;
  return array_literal;
}

NodePtr Parser::ParseExpressionList(Token::Type end)
{
  std::vector<NodePtr> elements;

  if (IsPeekToken(end))
  {
    NextToken();
    return std::make_shared<TupleNode>(current_token, elements);
  }
  NextToken();

  if (IsCurrentToken(Token::Type::KEYWORD_ASSIGN))
  {
    NextToken();
    NodePtr argument = ParseExpression(LOWEST);
    NextToken();
    elements.push_back(ParseKeyValueArgument(argument));
  }
  else
    elements.push_back(ParseExpression(LOWEST));

  while (IsPeekToken(Token::Type::COMMA_OPERATOR))
  {
    NextToken();
    if (!IsPeekToken(end))
    {
      NextToken();

      if (IsCurrentToken(Token::Type::KEYWORD_ASSIGN))
      {
        NextToken();
        NodePtr argument = ParseExpression(LOWEST);
        NextToken();
        elements.push_back(ParseKeyValueArgument(argument));
      }
      else
        elements.push_back(ParseExpression(LOWEST));
    }
    else
    {
      break;
    }
  }

  if (!ExpectPeek(end))
    return std::make_shared<TupleNode>(current_token);

  return std::make_shared<TupleNode>(current_token, elements);
}

NodePtr Parser::ParseIndexExpression(NodePtr left)
{
  IndexExpressionNodePtr expression = std::make_shared<IndexExpressionNode>(current_token, left);
  NextToken();
  expression->index = ParseExpression(LOWEST);
  if (!ExpectPeek(Token::Type::RIGHT_SQUARE_BRACKETS))
    return nullptr;
  return expression;
}

NodePtr Parser::ParseDotOperator(NodePtr left)
{
  NextToken();
  NodePtr right = ParseExpression(ADDITION_SUBTRACTION,
                                  {Token::Type::SEMI_COLON_OPERATOR, Token::Type::RIGHT_PARENTHESIS, Token::Type::DOT_OPERATOR});
  CallExpressionNodePtr call_expression = std::dynamic_pointer_cast<CallExpressionNode>(right);
  if (call_expression != nullptr)
    call_expression->arguments->elements.insert(call_expression->arguments->elements.begin(), left);
  return call_expression;
}

NodePtr Parser::ParseHashLiteral()
{
  HashLiteralNodePtr result = std::make_shared<HashLiteralNode>(current_token);
  NextToken();
  size_t current_index = current_token_index;

  if (IsCurrentToken(Token::Type::COMMA_OPERATOR))
  {
    if (!ExpectPeek(Token::Type::RIGHT_CURLY_BRACES))
    {
      return nullptr;
    }
    return std::make_shared<SetLiteralNode>(current_token);
  }

  while (!IsCurrentToken(Token::Type::RIGHT_CURLY_BRACES))
  {
    NodePtr key = ParseExpression(LOWEST);

    if (IsPeekToken(Token::Type::COMMA_OPERATOR))
      return ParseSetLiteral(key, current_index); // this is not a dictionary but in fact a set

    if (!ExpectPeek(Token::Type::COLON_OPERATOR))
      return nullptr;

    NextToken();
    NodePtr value = ParseExpression(LOWEST);

    if (result->pairs.find(key) != result->pairs.end())
      result->pairs[key] = value;
    else
      result->pairs.insert(std::make_pair(key, value)); // TODO: report warning/error?

    if (!IsPeekToken(Token::Type::RIGHT_CURLY_BRACES) && !ExpectPeek(Token::Type::COMMA_OPERATOR))
    {
      return nullptr;
    }
    NextToken();
  }
  return result;
}

NodePtr Parser::ParseSetLiteral(NodePtr first, size_t start_index)
{
  while (current_token_index >= start_index)
    PreviousToken();
  SetLiteralNodePtr set_literal = std::make_shared<SetLiteralNode>(current_token);
  NodePtr expression_list = ParseExpressionList(Token::Type::RIGHT_CURLY_BRACES);
  TupleNodePtr expression_tuple = std::dynamic_pointer_cast<TupleNode>(expression_list);
  set_literal->elements = expression_tuple->elements;
  return set_literal;
}

NodePtr Parser::ParseTernaryOperator(NodePtr left)
{
  IfExpressionNodePtr result = std::make_shared<IfExpressionNode>(current_token);
  NextToken();

  result->consequences.push_back(std::make_shared<BlockStatementNode>(current_token));
  result->consequences[0]->statements.push_back(left);

  result->conditions.push_back(ParseExpression(LOWEST,
                                               {Token::Type::SEMI_COLON_OPERATOR, Token::Type::END_OF_FILE, Token::Type::KEYWORD_ELSE}));

  if (!IsPeekToken(Token::Type::KEYWORD_ELSE))
  {
    result->alternative = nullptr;
  }
  else
  {
    NextToken();
    result->alternative = std::make_shared<BlockStatementNode>(current_token);
    NextToken();
    result->alternative->statements.push_back(ParseExpression(LOWEST));
  }

  return result;
}

NodePtr Parser::ParseTuple(NodePtr first, size_t start_index)
{
  TupleNodePtr result = std::make_shared<TupleNode>(current_token);
  while (current_token_index >= start_index)
    PreviousToken();

  NodePtr expression_list = ParseExpressionList(Token::Type::RIGHT_PARENTHESIS);
  TupleNodePtr expression_tuple = std::dynamic_pointer_cast<TupleNode>(expression_list);
  if (expression_tuple->elements.size() == 0)
  {
    if (first != nullptr)
    {
      result->elements.push_back(first);
      NextToken();
    }
    return result;
  }

  // NextToken();
  return expression_list;
}

NodePtr Parser::ParseArrowOperator(NodePtr left)
{
  FunctionLiteralNodePtr result = std::make_shared<FunctionLiteralNode>(current_token);

  if (left == nullptr)
    result->parameters = {};
  else
  {
    if (left->type != Node::Type::TUPLE && left->type != Node::Type::IDENTIFIER)
    {
      String brief_description = "cannot use " + left->ToString() +
                                 " as left-hand side of => operator";
      String detailed_description =
          " LHS of arrow operator needs to be an identifier or an identifier-tuple";
      ReportError(left->token, brief_description, detailed_description);
      return nullptr;
    }

    if (left->type == Node::Type::TUPLE)
    {
      TupleNodePtr function_parameters = std::dynamic_pointer_cast<TupleNode>(left);
      for (auto &parameter : function_parameters->elements)
      {
        IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(parameter);
        if (identifier != nullptr)
        {
          result->parameters.push_back(identifier);
        }
        else
        {
          std::cout << "Parameter " << parameter->ToString() << " is not a valid identifier" << std::endl;
        }
      }
    }
    else if (left->type == Node::Type::IDENTIFIER)
    {
      IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(left);
      if (identifier != nullptr)
      {
        result->parameters.push_back(identifier);
      }
      else
      {
        std::cout << "Parameter " << identifier->ToString() << " is not a valid identifier" << std::endl;
      }
    }
  }

  if (IsPeekToken(Token::Type::LEFT_CURLY_BRACES))
  {
    // Function body is a multi-statement block of code
    if (!ExpectPeek(Token::Type::LEFT_CURLY_BRACES))
      return nullptr;
    result->body = ParseBlockStatement();
  }
  else
  {
    NextToken();
    result->body = std::make_shared<BlockStatementNode>(current_token);
    NodePtr expression = ParseExpression(LOWEST);
    result->body->statements.push_back(expression);
  }

  return result;
}

NodePtr Parser::ParseKeyValueArgument(NodePtr left)
{
  KeyValueArgumentNodePtr result = std::make_shared<KeyValueArgumentNode>(current_token);
  NextToken();
  if (left->type == Node::Type::IDENTIFIER)
  {
    IdentifierNodePtr key = std::dynamic_pointer_cast<IdentifierNode>(left);
    result->key = key;
    NodePtr value = ParseExpression(LOWEST,
                                    {Token::Type::SEMI_COLON_OPERATOR, Token::Type::END_OF_FILE, Token::Type::COMMA_OPERATOR});

    // TODO: check if value is nullptr
    result->value = value;
  }
  else
  {
    // TODO: report error
  }
  return result;
}

} // namespace walnut