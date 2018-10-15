#include <parser.hpp>
#include <statements.hpp>

namespace parser
{
  std::shared_ptr<node> parser::parse_expression_statement()
  {
    std::shared_ptr<node> result = parse_expression(LOWEST);

    if (peek_token_is(lexer::token_type::SEMI_COLON_OPERATOR))
      next_token();

    return result;
  }
}