#include <parser.hpp>

namespace parser
{
  void parser::register_prefix_function(lexer::token_type token_type, std::function<std::shared_ptr<node>(void)> function) {
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

  void parser::register_infix_function(lexer::token_type token_type, std::function<std::shared_ptr<node>(std::shared_ptr<node>)> function) {
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
}