#include <token.hpp>
#include <string>

namespace lexer
{
  /* List of token strings - Used for debug printing */
  std::string token_strings[] = {
  #define TOKEN(label, string, value) string,
      TOKEN_LIST
  #undef TOKEN
      "invalid" };

  /* List of token values - Used for debug printing */
  std::string token_values[] = {
  #define TOKEN(label, string, value) value,
      TOKEN_LIST
  #undef TOKEN
      "invalid" };
}