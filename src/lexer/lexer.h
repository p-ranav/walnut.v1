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
list_t * tokenize(const char * file_path, long buffer_size, char * buffer);

// Consumes 1 unicode character
// buffer is the input buffer of characters (originally read from file)
// index is the index into the buffer where we are right now
// current_character points to the 1-byte character at buffer[index]
// the potentially multi-byte character is pointed to by next_character
// returns the width of next character
long consume(char * buffer, int * index, char * current_character, char ** multi_byte_character);

// Peek 1 unicode character
// buffer is the input buffer of characters (originally read from file)
// index is the index into the buffer where we are right now
// current_character points to the 1-byte character at buffer[index]
// the potentially multi-byte character is pointed to by next_character
// returns the width of next character
// 
// peek is similar to consume but index is not updated
long peek(char * buffer, int * index, char * current_character, char ** multi_byte_character);

// Return true (1) if the multi-byte character starts with input character
// If the multi_byte_character is NULL for some reason, return false
// else, compare first byte and return appropriate result
//
// This function will be extensively used in tokenize(...) to check if 
// the next character starts with, e.g., '/' or \" or \'
int startswith(char * multi_byte_character, long character_width, char character);

// Parse and remove comments
// checks both comments '// ...' and block comments /* ... */
// we're not creating tokens for these characters. consume and move on.
void parse_comments(long buffer_size, char * buffer, unsigned int * line, unsigned int * cursor, 
  int * index, char * current_character);

// Parse and save symbols - symbols include identifiers and keywords
// this function DOES NOT try to separate identifiers from keywords. Both are legally symbols.
// saves to result linked list 
void parse_symbol(long buffer_size, char * buffer, const char * file_path, unsigned int * line, 
  unsigned int * cursor, int * index, char * current_character, long next_character_width, 
  char * next_character, list_t * tokens);

// Check if a multi-byte character is a valid symbol
// To take advantage of UTF-8, we'll have to treat bytes higher than 127 as 
// perfectly ordinary characters. A UTF-8 sequence can only start with values 
// 0xC0 or greater, so that's what I've used for checking the start of an 
// identifier. Within an identifier, you would also want to allow 
// characters >= 0x80, which is the range of UTF-8 continuation bytes.
int valid_symbol(long character_width, char * multi_byte_character);

#endif