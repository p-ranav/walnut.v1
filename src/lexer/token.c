#include <token.h>

char *token_strings[44] = {
#define TOKEN(label, string) string,
    TOKEN_LIST
#undef TOKEN
  "invalid"
};