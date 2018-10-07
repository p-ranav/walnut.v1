#include <test_lexer_token_eof.h>
#include <test_lexer_token_boolean.h>
#include <test_lexer_token_number.h>
#include <test_lexer_token_delimiters.h>
#include <test_lexer_token_comparison.h>
#include <test_lexer_token_brackets.h>
#include <test_lexer_token_arithmetic.h>
#include <test_lexer_token_assignment.h>

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

  /* Arithmetic operators */
  TEST_RUN(lexer_token_arithmetic_add);
  TEST_RUN(lexer_token_arithmetic_subtract);
  TEST_RUN(lexer_token_arithmetic_multiply);
  TEST_RUN(lexer_token_arithmetic_divide);
  TEST_RUN(lexer_token_arithmetic_modulus);

  /* Assignment operators */
  TEST_RUN(lexer_token_assignment);
  TEST_RUN(lexer_token_assignment_add_assign);
  TEST_RUN(lexer_token_assignment_subtract_assign);
  TEST_RUN(lexer_token_assignment_multiply_assign);
  TEST_RUN(lexer_token_assignment_divide_assign);
  TEST_RUN(lexer_token_assignment_modulus_assign);

  /* Done with testing. Generate report */
  GENERATE_TEST_REPORT();
}