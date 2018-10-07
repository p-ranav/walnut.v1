#ifndef MACROS_H
#define MACROS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arrlen(list) sizeof(list) / sizeof(list[0])

#define allocate(structure, size) \
  (structure *)malloc(sizeof(structure) * size)

#define deallocate(pointer) \
  if (pointer)              \
    free(pointer);          \
  pointer = NULL;

/* Lexer macros */
#define reset_cursor (*cursor) = 1
#define increment_cursor (*cursor) += 1
#define increment_line (*line) += 1
#define strequal(lhs, rhs) (strcmp(lhs, rhs) == 0)

#define save_token(token_to_save)      \
  node = list_node_new(token_to_save); \
  list_rpush(tokens, node);

/* used in lexer_post_process(...) */
#define IGNORE_NEXT_TOKEN 0
#define CHECK_NEXT_TOKEN 1
#define process_token(current_token_value, new_token_type)                                                                                \
  if (check_and_update_token(current_token, current_token_value, IGNORE_NEXT_TOKEN, next_token, "", new_token_type, current_token_value)) \
    continue;

#define process_token_sequence(current_token_value, next_token_value, new_token_type)                                                                                   \
  if (check_and_update_token(current_token, current_token_value, CHECK_NEXT_TOKEN, next_token, next_token_value, new_token_type, current_token_value next_token_value)) \
  {                                                                                                                                                                     \
    free(((struct token_t *)next_node->val)->value);                                                                                                                    \
    free(((struct token_t *)next_node->val));                                                                                                                           \
    list_remove(tokens, next_node);                                                                                                                                     \
    it->next = node->next;                                                                                                                                              \
    continue;                                                                                                                                                           \
  }

/* Parser macros */
#define return_precedence(token)                                                             \
  if (token == TOKEN_LEFT_PARANTHESIS)                                                       \
    return CALL;                                                                             \
  else if (token == TOKEN_EQUAL || token == TOKEN_NOT_EQUAL)                                 \
    return EQUAL;                                                                            \
  else if (token == TOKEN_LESSER || token == TOKEN_GREATER || token == TOKEN_LESSER_EQUAL || \
           token == TOKEN_GREATER_EQUAL)                                                     \
    return LESSGREATER;                                                                      \
  else if (token == TOKEN_ADD || token == TOKEN_SUBTRACT)                                    \
    return SUM;                                                                              \
  else if (token == TOKEN_MULTIPLY || token == TOKEN_DIVIDE || token == TOKEN_MODULUS)       \
    return PRODUCT;                                                                          \
  else                                                                                       \
    return LOWEST;

/* Tests */
#define TEST_CASE(test_name) int test_name (int * test_count, int * number_of_successful_tests, int * number_of_successful_assertions)
#define DECLARE_TEST(test_name) test_label = test_name; (*test_count)++; printf("%s...", test_label);
#define RETURN_TEST_SUCCESS() { printf(" [OK]\n"); (*number_of_successful_tests) += 1; return 1; }

#define TEST_CHECK(condition) \
  if (!(condition)) \
  {\
    printf(" [FAILED]\n"); \
    printf(" * [CHECK FAILED] %s, line %d: %s\n", __FILE__, __LINE__, #condition);\
    return 0; \
  }\
  else \
    (*number_of_successful_assertions)++;

#define TEST_LIST \
  int test_count = 0;\
  int number_of_successful_tests = 0;\
  int number_of_successful_assertions = 0;\
  int main(void)
#define TEST_RUN(test_name) \
  if (test_count == 0)\
    printf("--------------------------------------------------------------------------------\n");\
  printf("[TEST %d] ", (test_count + 1)); \
  test_name(&test_count, &number_of_successful_tests, &number_of_successful_assertions);

#define GENERATE_TEST_REPORT() \
  printf("--------------------------------------------------------------------------------\n");\
  printf("%d ASSERTIONS ACROSS %d TESTS HAVE PASSED\n", number_of_successful_assertions, test_count);\
  printf("%d/%d TESTS HAVE PASSED\n", number_of_successful_tests, test_count); \
  printf("TEST SUCCESS RATE: %.2f%%\n", (double)(number_of_successful_tests / test_count * 100));\
  printf("--------------------------------------------------------------------------------\n");\
  return 0;

#endif