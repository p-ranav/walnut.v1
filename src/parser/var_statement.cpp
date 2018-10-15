#include <parser.hpp>
#include <statements.hpp>

namespace parser
{
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
}