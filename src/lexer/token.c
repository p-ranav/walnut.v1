#include <token.h>

/* List of token strings - Used for debug printing */
const char *const token_strings[] = {
#define TOKEN(label, string) string,
    TOKEN_LIST
#undef TOKEN
    "invalid"};