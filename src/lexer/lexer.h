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

// Consumes 1 unicode character
// buffer is the input buffer of characters (originally read from file)
// index is the index into the buffer where we are right now
// current_character points to the 1-byte character at buffer[index]
// the potentially multi-byte character is pointed to by next_character
// returns the width of next character
long consume(char * buffer, int * index, char * current_character, char ** multi_byte_character);

// Return true (1) if the multi-byte character starts with input character
// If the multi_byte_character is NULL for some reason, return false
// else, compare first byte and return appropriate result
//
// This function will be extensively used in tokenize(...) to check if 
// the next character starts with, e.g., '/' or \" or \'
int startswith(char * multi_byte_character, long character_width, char character);

#endif