#include <lexer.h>

list_t * tokenize(long buffer_size, char * buffer) {
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
        printf("Detected start of comment");

    }

  }

  // return the list of tokens
  return tokens;
}

long consume(char * buffer, int * index, char * current_character, char ** multi_byte_character) {
  // get the width of this unicode character
  int character_width = u8_seqlen(current_character);

  // prepare character array to hold multi-byte character
  *multi_byte_character = (char *)malloc(sizeof(char) * character_width);
  memset(*multi_byte_character, '\0', sizeof(char) * character_width);

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

int startswith(char * multi_byte_character, long character_width, char character) {
  
  // If the multi-byte character is NULL for some reason, return false
  if (!multi_byte_character)
    return 0;

  // Compare the first byte of the multi-byte character with input character
  if (multi_byte_character[0] == character)
    return 1;
  else
    return 0;
}