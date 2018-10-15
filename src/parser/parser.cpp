#include <parser.hpp>
#include <types.hpp>
#include <statements.hpp>

namespace parser
{
parser::parser(const std::vector<lexer::token> &tokens) : current_token(lexer::token()),
                                                          peek_token(lexer::token()),
                                                          current_token_index(0),
                                                          ast({}),
                                                          tokens(tokens)
{
  precedences = {
      {lexer::token_type::LEFT_PARANTHESIS, CALL},
      {lexer::token_type::EQUALITY_OPERATOR, EQUAL},
      {lexer::token_type::INEQUALITY_OPERATOR, EQUAL},
      {lexer::token_type::LESSER_THAN_OPERATOR, LESSGREATER},
      {lexer::token_type::LESSER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
      {lexer::token_type::GREATER_THAN_OPERATOR, LESSGREATER},
      {lexer::token_type::GREATER_THAN_OR_EQUAL_OPERATOR, LESSGREATER},
      {lexer::token_type::ADDITION_OPERATOR, SUM},
      {lexer::token_type::SUBTRACTION_OPERATOR, SUM},
      {lexer::token_type::MULTIPLICATION_OPERATOR, PRODUCT},
      {lexer::token_type::DIVISION_OPERATOR, PRODUCT},
      {lexer::token_type::MODULUS_OPERATOR, PRODUCT},
  };

  // prefix parse functions
  register_prefix_function(lexer::token_type::SYMBOL, std::bind(&parser::parse_identifier, this));
  register_prefix_function(lexer::token_type::INTEGER, std::bind(&parser::parse_integer, this));
  register_prefix_function(lexer::token_type::DOUBLE, std::bind(&parser::parse_double, this));

}

void parser::parse_program()
{
  next_token();
  next_token();

  while (!peek_token_is(lexer::token_type::END_OF_FILE))
  {
    std::shared_ptr<node> statement = parse_statement();
    if (statement != nullptr)
    {
      ast.push_back(statement);
    }
    next_token();
  }
}

void parser::next_token()
{
  current_token = peek_token;
  current_token_index += 1;
  peek_token = lexer::token("", 1, 1, lexer::token_type::END_OF_FILE, "");
  if (current_token_index < tokens.size())
    peek_token = tokens[current_token_index];
}

bool parser::current_token_is(lexer::token_type value)
{
  return (current_token.type == value);
}

bool parser::peek_token_is(lexer::token_type value)
{
  return (peek_token.type == value);
}

bool parser::expect_peek(lexer::token_type value)
{
  if (peek_token_is(value))
  {
    next_token();
    return true;
  }
  else
  {
    throw std::runtime_error("expected token X, instead got token Y");
  }
}

std::shared_ptr<node> parser::parse_statement()
{
  switch (current_token.type)
  {
  case lexer::token_type::KEYWORD_VAR:
    return parse_var_statement();
    break;
  case lexer::token_type::KEYWORD_RETURN:
    return parse_return_statement();
    break;
  default:
    return parse_expression_statement();
    break;
  }
}

std::shared_ptr<node> parser::parse_var_statement()
{
  std::shared_ptr<var_statement_node> result = std::make_shared<var_statement_node>();

  if (!expect_peek(lexer::token_type::SYMBOL))
  {
    return nullptr;
  }
  result->name = std::make_shared<identifier_node>(current_token.value);

  if (!expect_peek(lexer::token_type::ASSIGNMENT_OPERATOR))
  {
    return nullptr;
  }

  // TODO: parse expression
  while (!current_token_is(lexer::token_type::SEMI_COLON_OPERATOR))
  {
    next_token();
  }

  return result;
}

std::shared_ptr<node> parser::parse_return_statement()
{
  std::shared_ptr<return_statement_node> result = std::make_shared<return_statement_node>();
  next_token();
  while (!current_token_is(lexer::token_type::SEMI_COLON_OPERATOR))
  {
    next_token();
  }
  return result;
}

void parser::register_prefix_function(lexer::token_type token_type, std::function<std::shared_ptr<node>(void)> function)
{
  if (prefix_parse_functions.find(token_type) != prefix_parse_functions.end())
  {
    prefix_parse_functions[token_type] = function;
  }
  else
  {
    prefix_parse_functions.insert(
        std::map<lexer::token_type, std::function<std::shared_ptr<node>(void)>>::value_type(token_type, function));
  }
}

void parser::register_infix_function(lexer::token_type token_type, std::function<std::shared_ptr<node>(std::shared_ptr<node>)> function)
{
  if (infix_parse_functions.find(token_type) != infix_parse_functions.end())
  {
    infix_parse_functions[token_type] = function;
  }
  else
  {
    infix_parse_functions.insert(
        std::map<lexer::token_type, std::function<std::shared_ptr<node>(std::shared_ptr<node>)>>::value_type(token_type, function));
  }
}

parser::precedence parser::peek_precedence()
{
  if (precedences.find(peek_token.type) != precedences.end())
    return precedences[peek_token.type];
  else
    return LOWEST;
}

parser::precedence parser::current_precedence()
{
  if (precedences.find(current_token.type) != precedences.end())
    return precedences[current_token.type];
  else
    return LOWEST;
}

std::shared_ptr<node> parser::parse_expression_statement()
{
  std::shared_ptr<node> result = parse_expression(LOWEST);

  if (peek_token_is(lexer::token_type::SEMI_COLON_OPERATOR))
    next_token();

  return result;
}

std::shared_ptr<node> parser::parse_expression(precedence precedence)
{
  std::function<std::shared_ptr<node>(void)> prefix = prefix_parse_functions[current_token.type];
  if (prefix == nullptr)
    return nullptr;

  std::shared_ptr<node> left_expression = prefix();

  while (!peek_token_is(lexer::token_type::SEMI_COLON_OPERATOR) && precedence < peek_precedence())
  {
    std::function<std::shared_ptr<node>(std::shared_ptr<node>)> infix = infix_parse_functions[peek_token.type];

    if (infix == nullptr)
      return left_expression;

    next_token();

    left_expression = infix(left_expression);
  }

  return left_expression;
}

std::shared_ptr<node> parser::parse_identifier()
{
  return std::make_shared<identifier_node>(current_token.value);
}

std::shared_ptr<node> parser::parse_integer()
{
  return std::make_shared<integer_node>(std::stoi(current_token.value));
}

std::shared_ptr<node> parser::parse_double()
{
  return std::make_shared<double_node>(std::stod(current_token.value));
}

} // namespace parser