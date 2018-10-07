#include <test_lexer_token_boolean.h>

TEST_LIST
{
  TEST_RUN(lexer_token_boolean_true);
  TEST_RUN(lexer_token_boolean_false);
  GENERATE_TEST_REPORT();
}