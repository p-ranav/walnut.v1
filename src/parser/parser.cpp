#include <parser.hpp>
#include <types.hpp>
#include <statements.hpp>

namespace parser
{
  parser::parser(const std::vector<lexer::token>& tokens) :
    current_token(lexer::token()),
    peek_token(lexer::token()),
    current_token_index(0),
    ast({}),
    tokens(tokens) {
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
}