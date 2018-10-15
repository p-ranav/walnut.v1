#include <parser.hpp>
#include <statements.hpp>

namespace parser
{
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