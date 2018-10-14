#pragma once
#include <token.hpp>
#include <node.hpp>
#include <vector>
#include <memory>

namespace parser
{
  class parser
  {
  public:
    explicit parser(const std::vector<lexer::token>& tokens) :
      current_token(lexer::token()),
      peek_token(lexer::token()),
      current_token_index(0),
      ast({}),
      tokens(tokens) {}
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
  };

}