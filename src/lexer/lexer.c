#include <lexer.h>

list_t * tokenize(const char * file_path, long buffer_size, char * buffer) {
  // initialize the result
  list_t * tokens = list_new();

  // initialize the lexer context
  unsigned int line = 1;
  unsigned int cursor = 1;

  long index = 0;
  while (index < buffer_size) { // run till end of file

    // get the next character from the buffer
    char character = buffer[index];

    // check if character is UTF-8 encoded unicode character
    if (isutf(character)) {

      // consume 1 multi-byte character
      char * next_character = NULL;
      long next_character_width = consume(buffer, &index, &character, &next_character);

      if (startswith(next_character, next_character_width, '/'))
        parse_comments(buffer_size, buffer, &line, &cursor, &index, &character);
      if (valid_symbol(next_character_width, next_character))
        parse_symbol(buffer_size, buffer, file_path, &line, &cursor, &index, &character,
          next_character_width, next_character, tokens);
      else if (whitespace(next_character_width, next_character))
        parse_whitespace(buffer_size, buffer, &line, &cursor, &index, &character);
      else if (startswith(next_character, next_character_width, '\"'))
        parse_string_literal(buffer_size, buffer, file_path, &line, &cursor, &index, &character,
          next_character_width, next_character, tokens);
      else if (isdigit(*next_character))
        parse_number(buffer_size, buffer, file_path, &line, &cursor, &index, &character,
          next_character_width, next_character, tokens);
      else if (ispunct(*next_character))
        parse_punctuation(buffer_size, buffer, file_path, &line, &cursor, &index, &character,
          next_character_width, next_character, tokens);

      if (next_character)
        free(next_character);

      continue;

    }

  }

  // return the list of tokens
  return tokens;
}

void print_tokens(list_t * tokens)
{
  // print tokens
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it))) {
    struct token_t * token = ((struct token_t *)node->val);
    trace("%s: %s\n", token_strings[token->type], token->value);
  }
  free(it);
}

void delete_tokens(list_t * tokens)
{
  // print tokens
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it))) {
    struct token_t * token = ((struct token_t *)node->val);
    free(token->value);
    free(token);
  }
  list_destroy(tokens);
  free(it);
}

long consume(char * buffer, long * index, char * current_character, char ** multi_byte_character) {
  // get the width of this unicode character
  int character_width = u8_seqlen(current_character);

  // prepare character array to hold multi-byte character
  *multi_byte_character = (char *)malloc(character_width + 1);
  memset(*multi_byte_character, '\0', character_width);

  // parse multi-byte unicode character
  int sequence_index = 0;
  while (sequence_index < character_width) {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';
  // return the width of the consumed multi-byte character
  return character_width;
}

long peek(char * buffer, long * index, char * current_character, char ** multi_byte_character) {
  // get the width of this unicode character
  int character_width = u8_seqlen(current_character);

  // prepare character array to hold multi-byte character
  *multi_byte_character = (char *)malloc(character_width + 1);
  memset(*multi_byte_character, '\0', character_width);

  // parse multi-byte unicode character
  int sequence_index = 0;
  while (sequence_index < character_width) {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';

  // undo changes to index and current_character
  *index -= character_width;
  (*current_character) = buffer[*index];

  // return the width of the consumed multi-byte character
  return character_width;
}

int startswith(char * multi_byte_character, long character_width, char character) {
  
  // if the multi-byte character is NULL for some reason, return false
  if (!multi_byte_character)
    return 0;

  // compare the first byte of the multi-byte character with input character
  if (multi_byte_character[0] == character)
    return 1;
  else
    return 0;
}

void parse_comments(long buffer_size, char * buffer, unsigned int * line, unsigned int * cursor, long * index, char * current_character)
{
  char * peek_character = NULL;
  long peek_character_width = consume(buffer, index, current_character, &peek_character);

  // check if next character starts with '/'
  // if yes, treat this as the start of a line comment
  if (startswith(peek_character, peek_character_width, '/'))
  {
    // loop until end of line comment, i.e., end of line or end of file
    while (!startswith(peek_character, peek_character_width, 0x0A) && (*index < buffer_size))
    {
      if (peek_character)
        free(peek_character);
      long peek_character_width = consume(buffer, index, current_character, &peek_character);
      (*cursor) += 1;
    }
  }
  if (startswith(peek_character, peek_character_width, '*'))
  {
    // this is a block comment
    // consume characters till we encounter '*' followed by '/'
    while (1)
    {
      if (peek_character)
        free(peek_character);
      long peek_character_width = consume(buffer, index, current_character, &peek_character);
      (*cursor) += 1;
      
      if (startswith(peek_character, peek_character_width, EOF))
        error("block comment not terminated before end of file\n");
      
      if (startswith(peek_character, peek_character_width, 0x0A))
      {
        // end of line. increment line, reset cursor, and continue
        (*line) += 1;
        (*cursor) = 1;
        continue;
      }

      if (startswith(peek_character, peek_character_width, '*'))
      {
        // peek into the next character. We're hoping for '/' to close out the block comment
        if (peek_character)
          free(peek_character);
        long peek_character_with = peek(buffer, index, current_character, &peek_character);
        
        if (startswith(peek_character, peek_character_width, EOF))
          error("block comment not terminated before end of file\n");

        if (startswith(peek_character, peek_character_width, '/'))
        {
          if (peek_character)
            free(peek_character);
          consume(buffer, index, current_character, &peek_character);
          if (peek_character)
            free(peek_character);
          consume(buffer, index, current_character, &peek_character);
          (*cursor) += 1;
          if (peek_character)
            free(peek_character);
          return;
        }
        if (peek_character)
          free(peek_character);
      }
    }
  }
  if (peek_character)
    free(peek_character);

}

void parse_symbol(long buffer_size, char * buffer, const char * file_path, unsigned int * line, 
  unsigned int * cursor, long * index, char * current_character,
  long next_character_width, char * next_character, list_t * tokens) {
  
  // create a "symbol" token
  struct token_t * symbol = (struct token_t*)malloc(sizeof(struct token_t));
  symbol->file_path = file_path;
  symbol->line = *line;
  symbol->cursor = *cursor;
  symbol->type = TOKEN_SYMBOL;

  symbol->value = (char *)malloc(next_character_width + 1);
  long i;
  for (i = 0; i < next_character_width; i++)
  {
    symbol->value[i] = next_character[i];
  }
  symbol->value[next_character_width] = '\0';

  long current_size = next_character_width;
  long current_index = next_character_width;
  while (1)
  {
    char * peek_character = NULL;
    long peek_character_width = peek(buffer, index, current_character, &peek_character);

    if (valid_symbol(peek_character_width, peek_character))
    {
      // consume peek_character_width bytes
      if (peek_character)
        free(peek_character);

      peek_character_width = consume(buffer, index, current_character, &peek_character);

      // since we treat this as a single character, update cursor by 1
      cursor += 1;

      // reallocate space in symbol->value and copy this peek_character
      // the way this is done here is probably not efficient
      // I'm reallocating after each multi-byte character is consumed
      append_to(&symbol->value, &current_size, &peek_character, &peek_character_width);

      if (peek_character)
        free(peek_character);

      // continue to next character
      continue;
    }

    if (peek_character)
      free(peek_character);

    break;
  }
  list_node_t *node = list_node_new(symbol);
  list_rpush(tokens, node);
}

int valid_symbol(long character_width, char * multi_byte_character) {
  if (!multi_byte_character)
    return 0;

  if (character_width == 0)
    return 0;

  int result = 1;
  // check every byte in multi-byte character
  // if the characters conform to these rules, its a valid symbol
  long i;
  for (i = 0; i < character_width; i++) {
    char character = multi_byte_character[0];
    result *= (
      (character >= 'A' && character <= 'Z') ||
      (character >= 'a' && character <= 'z') ||
      (character == '_') ||
      ((unsigned char)character >= 0xC0) ||
      ((unsigned char)character >= 0x80));
  }
  return result;
}

void append_to(char ** lhs, long * lhs_size, char ** rhs, long * rhs_size) 
{
  // reallocate space in lhs and copy rhs
  char * realloc_lhs = realloc(*lhs, *lhs_size + *rhs_size + 1);
  if (!realloc_lhs) {
    error("realloc failed!\n");
    exit(EXIT_FAILURE);
  }
  *lhs = realloc_lhs;

  // save new multi-byte character
  long i;
  for (i = 0; i < (*rhs_size); i++) {
    (*lhs)[(*lhs_size)] = (*rhs)[i];
    (*lhs_size) += 1;
  }
  (*lhs)[(*lhs_size)] = '\0'; // null terminate the updated LHS
}

void parse_whitespace(long buffer_size, char * buffer, unsigned int * line, unsigned int * cursor,
  long * index, char * current_character) 
{
  while (1)
  {
    // loop here until we stop encountering 'space' characters
    char * peek_character = NULL;
    long peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (whitespace(peek_character_width, peek_character))
    {
      if (peek_character)
        free(peek_character);
      peek_character_width = consume(buffer, index, current_character, &peek_character);
      if (peek_character)
        free(peek_character);
      (*cursor) += 1;
      continue;
    }
    if (peek_character)
      free(peek_character);
    return; // break out of this loop
  }
  // we don't need to store whitespace tokens in the result
}

int whitespace(long character_width, char * multi_byte_character) {
  if (
    startswith(multi_byte_character, character_width, ' ') ||
    startswith(multi_byte_character, character_width, 0x09) ||
    startswith(multi_byte_character, character_width, 0x08) ||
    startswith(multi_byte_character, character_width, 0x0D)
    )
    return 1;
  else
    return 0;
}

void parse_string_literal(long buffer_size, char * buffer, const char * file_path, unsigned int * line,
  unsigned int * cursor, long * index, char * current_character, long next_character_width,
  char * next_character, list_t * tokens) 
{
  // create a "string" token
  struct token_t * string = (struct token_t*)malloc(sizeof(struct token_t));
  string->file_path = file_path;
  string->line = *line;
  string->cursor = *cursor;
  string->type = TOKEN_STRING_LITERAL;

  string->value = NULL;
  long current_size = 0;
  while (1)
  {
    // loop till we encounter the closing double quotes
    char * character_in_string = NULL;
    long character_in_string_width = peek(buffer, index, current_character, &character_in_string);
    (*cursor) += 1;

    if (startswith(character_in_string, character_in_string_width, '\\'))
    {
      if (character_in_string)
        free(character_in_string);

      // escape sequence
      char * peek_character = NULL;
      long peek_character_width = consume(buffer, index, current_character, &peek_character);
      if (startswith(peek_character, peek_character_width, '\"') ||
        startswith(peek_character, peek_character_width, '\\'))
      {
        // realloc and add '\\' to string->value
        //char * escape = "\\";
        //long escape_size = 1;
        //append_to(&string->value, &current_size, &escape, &escape_size);

        if (peek_character)
          free(peek_character);

        peek_character_width = consume(buffer, index, current_character, &peek_character);
        (*cursor) += 1;

        // realloc and add peek_character to string->value
        append_to(&string->value, &current_size, &peek_character, &peek_character_width);

        if (peek_character)
          free(peek_character);

        continue;
      }

      // end of line or end of file before the closing quotes
      if (startswith(peek_character, peek_character_width, 0x0A) ||
        startswith(peek_character, peek_character_width, EOF))
      {
        if (peek_character)
          free(peek_character);
        // TODO: report this error a little better
        error("EOL/EOF encountered before closing literal quotes\n");
      }

      // realloc and add peek_character to string->value
      append_to(&string->value, &current_size, &peek_character, &peek_character_width);

      if (peek_character)
        free(peek_character);
      continue;
    }

    // Add to string literal if not closing quotes or end of file
    if (!startswith(character_in_string, character_in_string_width, '\"') &&
        !startswith(character_in_string, character_in_string_width, EOF))
    {
      if (character_in_string)
        free(character_in_string);

      // realloc and add character_in_string to string->value
      char * character_in_string = NULL;
      long character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      append_to(&string->value, &current_size, &character_in_string, &character_in_string_width);

      if (character_in_string)
        free(character_in_string);
      continue;
    }

    // end of line or end of file before the closing quotes
    if (startswith(character_in_string, character_in_string_width, 0x0A) ||
      startswith(character_in_string, character_in_string_width, EOF))
    {
      // TODO: report this error a little better
      error("EOL/EOF encountered before closing literal quotes\n");
    }
    // consume the closing double quotes
    if (character_in_string)
      free(character_in_string);

    character_in_string = NULL;
    consume(buffer, index, current_character, &character_in_string);

    if (character_in_string)
      free(character_in_string);
    break;
  }
  list_node_t *node = list_node_new(string);
  list_rpush(tokens, node);
}

void parse_number(long buffer_size, char * buffer, const char * file_path, unsigned int * line,
  unsigned int * cursor, long * index, char * current_character, long next_character_width,
  char * next_character, list_t * tokens)
{
  // create a "punctuation" token
  struct token_t * number = (struct token_t*)malloc(sizeof(struct token_t));
  number->file_path = file_path;
  number->line = *line;
  number->cursor = *cursor;
  number->type = TOKEN_NUMBER;
  number->value = (char*)malloc(2);
  number->value[0] = *next_character;
  number->value[1] = '\0';
  long current_size = 1;

  if (*next_character == '0')
  {
    char * peek_character = NULL;
    long peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (*peek_character == 'X' || *peek_character == 'x')
    {
      if (peek_character)
        free(peek_character);
      char * character_in_string = NULL;
      long character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      (*cursor) += 1;
      append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
      if (character_in_string)
        free(character_in_string);

      //char * peek_character = NULL;
      //long peek_character_width = peek(buffer, index, current_character, &peek_character);
      while (1)
      {
        char * character_in_string = NULL;
        long character_in_string_width = consume(buffer, index, current_character, &character_in_string);
        (*cursor) += 1;
        if (isxdigit(*character_in_string))
        {
          append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
          if (character_in_string)
            free(character_in_string);
          continue;
        }
        if (character_in_string)
          free(character_in_string);
        break;
      }
    }
    else {
      if (peek_character)
        free(peek_character);
    }
  }

  while (1)
  {
    char * peek_character = NULL;
    long peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (peek_character_width == 1 && (isdigit(*peek_character) || *peek_character == '.' || *peek_character == 'f'))
    {
      if (peek_character)
        free(peek_character);
      char * character_in_string = NULL;
      long character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      *cursor += 1;
      append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
      if (character_in_string)
        free(character_in_string);
      continue;
    }
    if (peek_character)
      free(peek_character);
    break;
  }

  list_node_t *node = list_node_new(number);
  list_rpush(tokens, node);
}

void parse_punctuation(long buffer_size, char * buffer, const char * file_path, unsigned int * line,
  unsigned int * cursor, long * index, char * current_character, long next_character_width,
  char * next_character, list_t * tokens)
{
  if (ispunct(*current_character))
  {
    // create a "punctuation" token
    struct token_t * punctuation = (struct token_t*)malloc(sizeof(struct token_t));
    punctuation->file_path = file_path;
    punctuation->line = *line;
    punctuation->cursor = *cursor;
    punctuation->type = TOKEN_PUNCTUATION;
    punctuation->value = (char *)malloc(2);
    punctuation->value[0] = (*current_character);
    punctuation->value[1] = '\0';

    list_node_t *node = list_node_new(punctuation);
    list_rpush(tokens, node);
  }
}