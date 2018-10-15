#include <parser.hpp>

namespace parser
{

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

}