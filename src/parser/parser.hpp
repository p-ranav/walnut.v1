#pragma once
#include <token.hpp>
#include <node.hpp>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace parser
{
class parser
{
public:
  explicit parser(const std::vector<lexer::token> &tokens);

  void parse_program();

  std::vector<lexer::token> tokens;
  std::vector<std::shared_ptr<node>> ast;
  size_t current_token_index;
  lexer::token current_token;
  lexer::token peek_token;

private:
  void next_token();
  bool current_token_is(lexer::token_type value);
  bool peek_token_is(lexer::token_type value);
  bool expect_peek(lexer::token_type value);

  std::shared_ptr<node> parse_statement();
  std::shared_ptr<node> parse_var_statement();
  std::shared_ptr<node> parse_return_statement();
  std::shared_ptr<node> parse_expression_statement();

  std::map<lexer::token_type, std::function<std::shared_ptr<node>(void)>> prefix_parse_functions;
  void register_prefix_function(lexer::token_type token, std::function<std::shared_ptr<node>(void)> function);

  std::map<lexer::token_type, std::function<std::shared_ptr<node>(std::shared_ptr<node>)>> infix_parse_functions;
  void register_infix_function(lexer::token_type token, std::function<std::shared_ptr<node>(std::shared_ptr<node>)> function);

  enum precedence
  {
    LOWEST,
    EQUAL,       /* ==, != */
    LESSGREATER, /* >, >=, < and <= */
    SUM,         /* +, - */
    PRODUCT,     /* *, /, % */
    PREFIX,      /* -X or !X */
    CALL         /* my_function(X) */
  };
  std::map<lexer::token_type, precedence> precedences;

  precedence peek_precedence();
  precedence current_precedence();
  std::shared_ptr<node> parse_expression(precedence precedence);

  /* Prefix parse functions */
  std::shared_ptr<node> parse_identifier();
  std::shared_ptr<node> parse_integer();
  std::shared_ptr<node> parse_double();
};

} // namespace parser