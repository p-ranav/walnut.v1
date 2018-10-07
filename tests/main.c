#include <test_lexer_token_eof.h>
#include <test_lexer_token_boolean.h>
#include <test_lexer_token_number.h>
#include <test_lexer_token_delimiters.h>

TEST_MAIN
{
  /* Lexer Tests 
     The following tests check lexer.tokenize and confirm
     that the right tokens are returned by the lexer when 
     encountering specific input character buffers. 
  */
  /* Test end of file */
  TEST_RUN(lexer_token_eof);

  /* Test boolean */
  TEST_RUN(lexer_token_boolean_true);
  TEST_RUN(lexer_token_boolean_false);

  /* Test number */
  TEST_RUN(lexer_token_integer);
  TEST_RUN(lexer_token_float);
  TEST_RUN(lexer_token_double);

  /* Test delimiters */
  TEST_RUN(lexer_token_dot);
  TEST_RUN(lexer_token_comma);
  TEST_RUN(lexer_token_colon);
  TEST_RUN(lexer_token_semi_colon);
  TEST_RUN(lexer_token_exclamation);
  TEST_RUN(lexer_token_question);

  /* Done with testing. Generate report */
  GENERATE_TEST_REPORT();
}