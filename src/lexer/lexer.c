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

      // get the width of this unicode character
      int character_width = u8_seqlen(&character);

      // prepare character array to hold multi-byte character
      char * unicode_character = (char *)malloc(sizeof(char) * character_width);
      memset(unicode_character, '\0', sizeof(char) * character_width);

      // parse multi-byte unicode character
      int sequence_index = 0;
      while (sequence_index < character_width) {
        character = buffer[index];
        index += 1;
        sequence_index += 1;
        unicode_character[sequence_index - 1] = character;
      }
      unicode_character[sequence_index] = '\0';

      trace("%s", unicode_character);

    }

  }

  // return the list of tokens
  return tokens;
}