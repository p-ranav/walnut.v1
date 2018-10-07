#include <test_lexer_token_eof.h>
#include <test_lexer_token_boolean.h>
#include <test_lexer_token_number.h>
#include <test_lexer_token_delimiters.h>
#include <test_lexer_token_comparison.h>
#include <test_lexer_token_brackets.h>

TEST_MAIN
{
  /* Lexer Tests 
     The following tests check lexer.tokenize and confirm
     that the right tokens are returned by the lexer when 
     encountering specific input character buffers. 
  */
  /* End of file */
  TEST_RUN(lexer_token_eof);

  /* Boolean */
  TEST_RUN(lexer_token_boolean_true);
  TEST_RUN(lexer_token_boolean_false);

  /* Test number */
  TEST_RUN(lexer_token_integer);
  TEST_RUN(lexer_token_float);
  TEST_RUN(lexer_token_double);

  /* Delimiters */
  TEST_RUN(lexer_token_dot);
  TEST_RUN(lexer_token_comma);
  TEST_RUN(lexer_token_colon);
  TEST_RUN(lexer_token_semi_colon);
  TEST_RUN(lexer_token_exclamation);
  TEST_RUN(lexer_token_question);

  /* Comparison operators */
  TEST_RUN(lexer_token_comparison_equal);
  TEST_RUN(lexer_token_comparison_not_equal);
  TEST_RUN(lexer_token_comparison_greater);
  TEST_RUN(lexer_token_comparison_greater_equal);
  TEST_RUN(lexer_token_comparison_lesser);
  TEST_RUN(lexer_token_comparison_lesser_equal);

  /* Brackets, braces and paranthesis */
  TEST_RUN(lexer_token_brackets_left_paranthesis);
  TEST_RUN(lexer_token_brackets_left_curly_braces);
  TEST_RUN(lexer_token_brackets_left_square_brackets);
  TEST_RUN(lexer_token_brackets_right_paranthesis);
  TEST_RUN(lexer_token_brackets_right_curly_braces);
  TEST_RUN(lexer_token_brackets_right_square_brackets);

  /* Done with testing. Generate report */
  GENERATE_TEST_REPORT();
}