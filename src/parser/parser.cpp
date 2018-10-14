#include <parser.hpp>
#include <types.hpp>
#include <statements.hpp>

namespace parser
{
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
    peek_token = lexer::token("", 1, 1, lexer::token_type::INVALID, "");
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
      // return parse_expression_statement();
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
    while (!current_token_is(lexer::token_type::SEMI_COLON_OPERATOR)) {
      next_token();
    }
    return result;
  }
}