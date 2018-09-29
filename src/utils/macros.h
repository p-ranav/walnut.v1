#ifndef MACROS_H
#define MACROS_H

#define deallocate(pointer) \
  if (pointer)              \
    free(pointer);          \
  pointer = NULL;

/* Lexer macros */
#define strequal(lhs, rhs) (strcmp(lhs, rhs) == 0)

/* used in lexer_post_process(...) */
#define IGNORE_NEXT_TOKEN 0
#define CHECK_NEXT_TOKEN 1
#define process_token(current_token_value, new_token_type) \
  if (check_and_update_token(current_token, current_token_value, IGNORE_NEXT_TOKEN, next_token, "", new_token_type, current_token_value)) \
    continue;

#define process_token_sequence(current_token_value, next_token_value, new_token_type) \
  if (check_and_update_token(current_token, current_token_value, CHECK_NEXT_TOKEN, next_token, next_token_value, new_token_type, current_token_value ## next_token_value)) { \
    list_remove(tokens, next_node); \
    it->next = node->next; \
    continue; \
  }

#endif