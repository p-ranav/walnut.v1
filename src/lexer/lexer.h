#ifndef LEXER_H
#define LEXER_H
#include <token.h>
#include <utf8.h>
#include <list.h>
#include <macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*The lexer needs to do the following:
(1) Take the sequence of bytes in the input buffer
(2) correctly parsing unicode characters (UTF-8 encoding)
(3) tokenize the stream of characters (build a list of tokens)
(4) return the list of tokens
Tokens can be of different categories (see token.h)*/
list_t *lexer_tokenize(const char *file_path, long buffer_size, char *buffer);

/*Print tokens returned by tokenize(...)
<token_type>: <token_value>*/
void lexer_print(list_t *tokens);

/*Call free(token) for each token in tokens
Clean up memory consumed by token->value*/
void lexer_destroy(list_t *tokens);

/*Consumes 1 unicode character
buffer is the input buffer of characters (originally read from file)
index is the index into the buffer where we are right now
current_character points to the 1-byte character at buffer[index]
the potentially multi-byte character is pointed to by next_character
returns the width of next character*/
long consume(char *buffer, long *index, char *current_character, char **multi_byte_character);

/*Peek 1 unicode character
buffer is the input buffer of characters (originally read from file)
index is the index into the buffer where we are right now
current_character points to the 1-byte character at buffer[index]
the potentially multi-byte character is pointed to by next_character
returns the width of next character

peek is similar to consume but index is not updated*/
long peek(char *buffer, long *index, char *current_character, char **multi_byte_character);

/*Return true (1) if the multi-byte character starts with input character
If the multi_byte_character is NULL for some reason, return false
else, compare first byte and return appropriate result

This function will be extensively used in tokenize(...) to check if
the next character starts with, e.g., '/' or \" or \'*/
int startswith(char *multi_byte_character, long character_width, char character);

/*Parse and remove comments
checks both comments ' ...' and block comments / ... /
we're not creating tokens for these characters. consume and move on.*/
void parse_comments(long buffer_size, char *buffer, unsigned int *line, unsigned int *cursor,
                    long *index, char *current_character);

/*Parse and save symbols - symbols include identifiers and keywords
this function DOES NOT try to separate identifiers from keywords. Both are legally symbols.
saves to result linked list*/
void parse_symbol(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character, long next_character_width,
                  char *next_character, list_t *tokens);

/*Check if a multi-byte character is a valid symbol
To take advantage of UTF-8, we'll have to treat bytes higher than 127 as
perfectly ordinary characters. A UTF-8 sequence can only start with values
0xC0 or greater, so that's what I've used for checking the start of an
identifier. Within an identifier, you would also want to allow
characters >= 0x80, which is the range of UTF-8 continuation bytes.*/
int valid_symbol(long character_width, char *multi_byte_character);

/*Helper function to append two unicode multi-byte character arrays
what I want here is lhs += rhs where lhs and rhs are character arrays*/
void append_to(char **lhs, long *lhs_size, char **rhs, long *rhs_size);

/*Parse and ignore whitespace*/
void parse_whitespace(long buffer_size, char *buffer, unsigned int *cursor,
                      long *index, char *current_character);

/* check if a multi-byte character is a space character */
int whitespace(long character_width, char *multi_byte_character);

/*check if a multi-byte character is a string literal, e.g., "Hello World"
accept everything between double quotes
push string literal to end of tokens when done */
void parse_string_literal(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                          unsigned int *cursor, long *index, char *current_character, list_t *tokens);

/*check if a multi-byte character is a digit
accept everything until next character is not a digit
create number token and push to end of tokens*/
void parse_number(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character,
                  char *next_character, list_t *tokens);

/*check if a multi-byte character is an ASCII special character, e.g., *, /, ;, - etc.
  accept 1 character
  create punctuation token and push to end of tokens*/
void parse_punctuation(const char *file_path, unsigned int *line,
                       unsigned int *cursor, char *current_character, list_t *tokens);

/* lexer_post_process 
   This function takes token classification to the next level
   lexer_tokenize returns a list of tokens. one of the following types:
   (1) symbol, (2) number, (3) punctuation, (4) string, (5) comments, and (6) whitespace

   this post-processing function is responsible for:
   classifying a symbol token as either: (1) identifier, or (2) keyword
   classifying punctuations as concrete tokens, e.g., ';' as TOKEN_SEMICOLON
   (maybe) classifying number as INTEGER or FLOAT or DOUBLE

   these concrete classifications instead of SYMBOL, PUNCTUATION etc., are to 
   make the parser stage easier
*/
void lexer_post_process(list_t *tokens);

/* Helper functions used by lexer_post_process(...) to update the token value */
int check_and_update_token(struct token_t *current_token, char *current_token_value,
                           int check_next_token, /* should next token be considered or is checking current_token enough? */
                           struct token_t *next_token, char *next_token_value, token new_type, char *new_value);
void update_token_type(struct token_t *current_token, token new_type);
void update_token_value(struct token_t *current_token, const char *new_value);

#endif