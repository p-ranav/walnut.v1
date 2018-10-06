#ifndef MACROS_H
#define MACROS_H

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

#endif