#ifndef LEXER_H
#define LEXER_H
#include <token.h>
#include <utf8.h>
#include <list.h>
#include <macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The lexer needs to do the following:
// (1) Take the sequence of bytes in the input buffer
// (2) correctly parsing unicode characters (UTF-8 encoding)
// (3) tokenize the stream of characters (build a list of tokens)
// (4) return the list of tokens
// Tokens can be of different categories (see token.h)
list_t * tokenize(long buffer_size, char * buffer);

#endif