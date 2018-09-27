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

      // Print unicode character for debugging
      trace("%s", next_character);

      if (startswith(next_character, next_character_width, '/'))
        parse_comments(buffer_size, buffer, &line, &cursor, &index, &character);
      else if (valid_symbol(next_character_width, next_character))
        parse_symbol(buffer_size, buffer, file_path, &line, &cursor, &index, &character, 
          next_character_width, next_character, tokens);
    }

  }

  // print tokens
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it))) {
    struct token_t * token = ((struct token_t *)node->val);
    trace("%s: %s\n", token_strings[token->type], token->value);
  }

  // return the list of tokens
  return tokens;
}

long consume(char * buffer, long * index, char * current_character, char ** multi_byte_character) {
  // get the width of this unicode character
  int character_width = u8_seqlen(current_character);

  // prepare character array to hold multi-byte character
  *multi_byte_character = (char *)malloc(character_width);
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
  *multi_byte_character = (char *)malloc(character_width);
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
  char * peek_character;
  long peek_character_width = consume(buffer, index, current_character, &peek_character);

  // check if next character starts with '/'
  // if yes, treat this as the start of a line comment
  if (startswith(peek_character, peek_character_width, '/'))
  {
    // loop until end of line comment, i.e., end of line or end of file
    while (!startswith(peek_character, peek_character_width, 0x0A) && (*index < buffer_size))
    {
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
        long peek_character_with = peek(buffer, index, current_character, &peek_character);
        
        if (startswith(peek_character, peek_character_width, EOF))
          error("block comment not terminated before end of file\n");

        if (startswith(peek_character, peek_character_width, '/'))
        {
          consume(buffer, index, current_character, &peek_character);
          (*cursor) += 1;
          break;
        }
      }
    }
  }
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
      peek_character_width = consume(buffer, index, current_character, &peek_character);

      // since we treat this as a single character, update cursor by 1
      cursor += 1;

      // reallocate space in symbol->value and copy this peek_character
      // the way this is done here is probably not efficient
      // I'm reallocating after each multi-byte character is consumed
      current_size += peek_character_width;
      char * realloc_value = realloc(symbol->value, current_size + 1);
      if (!realloc_value) {
        error("realloc failed!\n");
        exit(EXIT_FAILURE);
      }
      symbol->value = realloc_value;
      
      // save new multi-byte character
      long i;
      for (i = 0; i < peek_character_width; i++) {
        symbol->value[current_index] = peek_character[i];
        current_index += 1;
      }
      symbol->value[current_index] = '\0';

      // continue to next character
      continue;
    }

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