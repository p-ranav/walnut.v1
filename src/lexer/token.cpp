#include <token.hpp>

/* List of token strings - Used for debug printing */
const char *const token_strings[] = {
#define TOKEN(label, string, value) string,
    TOKEN_LIST
#undef TOKEN
    "invalid" };

/* List of token values - Used for debug printing */
const char *const token_values[] = {
#define TOKEN(label, string, value) value,
    TOKEN_LIST
#undef TOKEN
    "invalid" };