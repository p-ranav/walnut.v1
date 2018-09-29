#include <token.h>

const char * const token_strings[] = {
#define TOKEN(label, string) string,
    TOKEN_LIST
#undef TOKEN
  "invalid"
};