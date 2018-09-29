#include <lexer.h>

extern const char *const token_strings[];

list_t *lexer_tokenize(const char *file_path, long buffer_size, char *buffer)
{
  /* Declarations */
  list_t *tokens;
  unsigned int line;
  unsigned int cursor;
  long index;
  char character;
  char *next;
  long next_width;

  /* initialize the result */
  tokens = list_new();

  /* initialize the lexer context */
  line = 1;
  cursor = 1;

  index = 0;
  while (index < buffer_size)
  { /* run till end of file */

    /* get the next character from the buffer */
    character = buffer[index];

    /* check if character is UTF-8 encoded unicode character */
    if (isutf(character))
    {

      /* consume 1 multi-byte character */
      next = NULL;
      next_width = consume(buffer, &index, &character, &next);

      /* check first if this is the start of a comment section */
      if (startswith(next, next_width, '/'))
        parse_comments(buffer_size, buffer, &line, &cursor, &index, &character);

      /* now check if the next character is the start of symbol - identifier or keyword */
      if (valid_symbol(next_width, next))
        parse_symbol(buffer_size, buffer, file_path, &line, &cursor, &index,
                     &character, next_width, next, tokens);

      /* consume all whitespace */
      else if (whitespace(next_width, next))
        parse_whitespace(buffer_size, buffer, &cursor, &index, &character);

      /* check if the next character is the start of a string literal, e.g., "Hello World" */
      else if (startswith(next, next_width, '\"'))
        parse_string_literal(buffer_size, buffer, file_path, &line, &cursor, &index, &character, tokens);

      /* check if the next character is the start of a number. Consume till end of number */
      else if (isdigit(*next))
        parse_number(buffer_size, buffer, file_path, &line, &cursor, &index, &character, next, tokens);

      /* check if next character is a punctuation. if so, consume 1 character and move on */
      else if (ispunct(*next))
        parse_punctuation(file_path, &line, &cursor, &character, tokens);

      /* we've made the most out of 'next' - deallocate it before looping again. */
      deallocate(next);

      continue;
    }
  }

  /* return the list of tokens */
  return tokens;
}

void lexer_print(list_t *tokens)
{
  /* use list_iterator to iterate over list of tokens */
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it)))
  {
    /* get pointer to token and print token type and value */
    struct token_t *token = ((struct token_t *)node->val);
    const char * token_string = token_strings[token->type];

    /* add spaces for pretty print */
    int length = strlen(token_string);
    int num_spaces_to_add = 20 - length;
    char * spaces = (char *)malloc(num_spaces_to_add + 1);
    memset(spaces, ' ', num_spaces_to_add + 1);
    spaces[num_spaces_to_add] = '\0';

    /* pretty print lexer tokens */
    printf("%s%s: %s\n", token_strings[token->type], spaces, token->value);
  }
  deallocate(it);
}

void lexer_destroy(list_t *tokens)
{
  /* use list_iterator to iterate over list of tokens */
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it)))
  {
    /* get pointer to token */
    struct token_t *token = ((struct token_t *)node->val);

    /* deallocate the char* value of the token */
    deallocate(token->value);

    /* deallocate the token itself */
    deallocate(token);
  }
  list_destroy(tokens);
  deallocate(it);
}

long consume(char *buffer, long *index, char *current_character, char **multi_byte_character)
{
  /* declarations */
  int character_width;
  int sequence_index;

  /* get the width of this unicode character */
  character_width = u8_seqlen(current_character);

  /* prepare character array to hold multi-byte character */
  *multi_byte_character = (char *)malloc(character_width + 1);
  memset(*multi_byte_character, '\0', character_width);

  /* parse multi-byte unicode character */
  sequence_index = 0;
  while (sequence_index < character_width)
  {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';
  /* return the width of the consumed multi-byte character */
  return character_width;
}

long peek(char *buffer, long *index, char *current_character, char **multi_byte_character)
{
  /* declarations */
  int character_width;
  int sequence_index;

  /* get the width of this unicode character */
  character_width = u8_seqlen(current_character);

  /* prepare character array to hold multi-byte character */
  *multi_byte_character = (char *)malloc(character_width + 1);
  memset(*multi_byte_character, '\0', character_width);

  /* parse multi-byte unicode character */
  sequence_index = 0;
  while (sequence_index < character_width)
  {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';

  /* undo changes to index and current_character */
  *index -= character_width;
  (*current_character) = buffer[*index];

  /* return the width of the peek'd multi-byte character */
  return character_width;
}

int startswith(char *multi_byte_character, long character_width, char character)
{

  /* if the multi-byte character is NULL for some reason, return false */
  if (!multi_byte_character || character_width == 0)
    return 0;

  /* compare the first byte of the multi-byte character with input character */
  if (multi_byte_character[0] == character)
    return 1;
  else
    return 0;
}

void parse_comments(long buffer_size, char *buffer, unsigned int *line, unsigned int *cursor, long *index, char *current_character)
{
  char *peek_character = NULL;
  long peek_character_width;

  peek_character_width = consume(buffer, index, current_character, &peek_character);

  /* check if next character starts with '/'
     if yes, treat this as the start of a line comment */
  if (startswith(peek_character, peek_character_width, '/'))
  {
    /* loop until end of line comment, i.e., end of line or end of file */
    while (!startswith(peek_character, peek_character_width, 0x0A) && (*index < buffer_size))
    {
      deallocate(peek_character);
      peek_character_width = consume(buffer, index, current_character, &peek_character);
      (*cursor) += 1;
    }
  }
  if (startswith(peek_character, peek_character_width, '*'))
  {
    /* this is a block comment
       consume characters till we encounter '*' followed by '/' */
    while (1)
    {
      deallocate(peek_character);
      peek_character_width = consume(buffer, index, current_character, &peek_character);
      (*cursor) += 1;

      if (startswith(peek_character, peek_character_width, EOF))
      {
        fprintf(stderr, "block comment not terminated before end of file\n");
        exit(EXIT_FAILURE);
      }

      if (startswith(peek_character, peek_character_width, 0x0A))
      {
        /* end of line. increment line, reset cursor, and continue */
        (*line) += 1;
        (*cursor) = 1;
        continue;
      }

      if (startswith(peek_character, peek_character_width, '*'))
      {
        /* peek into the next character. We're hoping for '/' to close out the block comment */
        deallocate(peek_character);
        peek_character_width = peek(buffer, index, current_character, &peek_character);

        /* error condition: we reach EOF before the block comment is closed */
        if (startswith(peek_character, peek_character_width, EOF))
        {
          fprintf(stderr, "block comment not terminated before end of file\n");
          exit(EXIT_FAILURE);
        }

        if (startswith(peek_character, peek_character_width, '/'))
        {
          /* peek is a '/' - deallocate and then consume */
          deallocate(peek_character);

          /* consume this character and return */
          consume(buffer, index, current_character, &peek_character);
          deallocate(peek_character);

          consume(buffer, index, current_character, &peek_character);
          (*cursor) += 1;
          deallocate(peek_character);

          return;
        }
        deallocate(peek_character);
      }
    }
  }
  deallocate(peek_character);
}

void parse_symbol(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character,
                  long next_character_width, char *next_character, list_t *tokens)
{
  /* declarations */
  long i;
  long current_size;
  char *peek_character;
  long peek_character_width;
  list_node_t *node;
  struct token_t *symbol;

  if (buffer_size == 0)
    return;

  /* create a "symbol" token */
  symbol = (struct token_t *)malloc(sizeof(struct token_t));
  symbol->file_path = file_path;
  symbol->line = *line;
  symbol->cursor = *cursor;
  symbol->type = TOKEN_SYMBOL;

  /* allocate sufficient space for storing symbol value */
  symbol->value = (char *)malloc(next_character_width + 1);
  for (i = 0; i < next_character_width; i++)
  { /* save one character at a time */
    symbol->value[i] = next_character[i];
  }
  symbol->value[next_character_width] = '\0';

  current_size = next_character_width;
  while (1)
  {
    peek_character = NULL;
    peek_character_width = peek(buffer, index, current_character, &peek_character);

    if (valid_symbol(peek_character_width, peek_character))
    {
      /* consume peek_character_width bytes */
      deallocate(peek_character);

      peek_character_width = consume(buffer, index, current_character, &peek_character);

      /* since we treat this as a single character, update cursor by 1 */
      cursor += 1;

      /* reallocate space in symbol->value and copy this peek_character
         the way this is done here is probably not efficient
         I'm reallocating after each multi-byte character is consumed */
      append_to(&symbol->value, &current_size, &peek_character, &peek_character_width);

      deallocate(peek_character);

      /* continue to next character */
      continue;
    }

    deallocate(peek_character);

    break;
  }
  node = list_node_new(symbol);
  list_rpush(tokens, node);
}

int valid_symbol(long character_width, char *multi_byte_character)
{
  /* declarations */
  int result;
  long i;

  if (!multi_byte_character)
    return 0;

  if (character_width == 0)
    return 0;

  result = 1;
  /* check every byte in multi-byte character
     if the characters conform to these rules, its a valid symbol */
  for (i = 0; i < character_width; i++)
  {
    char character = multi_byte_character[0];
    result *= ((character >= 'A' && character <= 'Z') ||
               (character >= 'a' && character <= 'z') ||
               (character == '_') ||
               ((unsigned char)character >= 0xC0) ||
               ((unsigned char)character >= 0x80));
  }
  return result;
}

void append_to(char **lhs, long *lhs_size, char **rhs, long *rhs_size)
{
  /* declarations */
  long i;

  /* reallocate space in lhs and copy rhs */
  char *realloc_lhs = realloc(*lhs, *lhs_size + *rhs_size + 1);
  if (!realloc_lhs)
  {
    fprintf(stderr, "realloc failed!\n");
    exit(EXIT_FAILURE);
  }
  *lhs = realloc_lhs;

  /* save new multi-byte character */
  for (i = 0; i < (*rhs_size); i++)
  {
    (*lhs)[(*lhs_size)] = (*rhs)[i];
    (*lhs_size) += 1;
  }
  (*lhs)[(*lhs_size)] = '\0'; /* null terminate the updated LHS */
}

void parse_whitespace(long buffer_size, char *buffer, unsigned int *cursor,
                      long *index, char *current_character)
{
  if (buffer_size == 0)
    return;

  while (1)
  {
    /* loop here until we stop encountering 'space' characters */
    char *peek_character = NULL;
    long peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (whitespace(peek_character_width, peek_character))
    {
      deallocate(peek_character);
      peek_character_width = consume(buffer, index, current_character, &peek_character);
      deallocate(peek_character);
      (*cursor) += 1;
      continue;
    }
    deallocate(peek_character);
    return; /* break out of this loop */
  }
  /* we don't need to store whitespace tokens in the result */
}

int whitespace(long character_width, char *multi_byte_character)
{
  if (
      startswith(multi_byte_character, character_width, ' ') ||
      startswith(multi_byte_character, character_width, 0x09) ||
      startswith(multi_byte_character, character_width, 0x08) ||
      startswith(multi_byte_character, character_width, 0x0D))
    return 1;
  else
    return 0;
}

void parse_string_literal(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                          unsigned int *cursor, long *index, char *current_character, list_t *tokens)
{
  /* declarations */
  long current_size;
  char *character_in_string;
  long character_in_string_width;
  char *peek_character;
  long peek_character_width;
  list_node_t *node;
  struct token_t *string;

  if (buffer_size == 0)
    return;

  /* create a "string" token */
  string = (struct token_t *)malloc(sizeof(struct token_t));
  string->file_path = file_path;
  string->line = *line;
  string->cursor = *cursor;
  string->type = TOKEN_STRING_LITERAL;

  string->value = NULL;
  current_size = 0;
  while (1)
  {
    /* loop till we encounter the closing double quotes */
    character_in_string = NULL;
    character_in_string_width = peek(buffer, index, current_character, &character_in_string);
    (*cursor) += 1;

    if (startswith(character_in_string, character_in_string_width, '\\'))
    {
      deallocate(character_in_string);

      /* escape sequence */
      peek_character = NULL;
      peek_character_width = consume(buffer, index, current_character, &peek_character);
      if (startswith(peek_character, peek_character_width, '\"') ||
          startswith(peek_character, peek_character_width, '\\'))
      {
        deallocate(peek_character);

        peek_character_width = consume(buffer, index, current_character, &peek_character);
        (*cursor) += 1;

        /* realloc and add peek_character to string->value */
        append_to(&string->value, &current_size, &peek_character, &peek_character_width);

        deallocate(peek_character);

        continue;
      }

      /* end of line or end of file before the closing quotes */
      if (startswith(peek_character, peek_character_width, 0x0A) ||
          startswith(peek_character, peek_character_width, EOF))
      {
        deallocate(peek_character);
        /* TODO: report this error a little better */
        fprintf(stderr, "EOL/EOF encountered before closing literal quotes\n");
        exit(EXIT_FAILURE);
      }

      /* realloc and add peek_character to string->value */
      append_to(&string->value, &current_size, &peek_character, &peek_character_width);

      deallocate(peek_character);
      continue;
    }

    /* Add to string literal if not closing quotes or end of file */
    if (!startswith(character_in_string, character_in_string_width, '\"') &&
        !startswith(character_in_string, character_in_string_width, EOF))
    {
      deallocate(character_in_string);

      /* realloc and add character_in_string to string->value */
      character_in_string = NULL;
      character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      append_to(&string->value, &current_size, &character_in_string, &character_in_string_width);

      deallocate(character_in_string);
      continue;
    }

    /* end of line or end of file before the closing quotes */
    if (startswith(character_in_string, character_in_string_width, 0x0A) ||
        startswith(character_in_string, character_in_string_width, EOF))
    {
      /* TODO: report this error a little better */
      fprintf(stderr, "EOL/EOF encountered before closing literal quotes\n");
      exit(EXIT_FAILURE);
    }
    /* consume the closing double quotes */
    deallocate(character_in_string);

    character_in_string = NULL;
    consume(buffer, index, current_character, &character_in_string);

    deallocate(character_in_string);
    break;
  }
  node = list_node_new(string);
  list_rpush(tokens, node);
}

void parse_number(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character,
                  char *next_character, list_t *tokens)
{
  /* declarations */
  long current_size;
  char *peek_character;
  long peek_character_width;
  char *character_in_string;
  long character_in_string_width;
  list_node_t *node;
  struct token_t *number;

  if (buffer_size == 0)
    return;

  /* create a "punctuation" token */
  number = (struct token_t *)malloc(sizeof(struct token_t));
  number->file_path = file_path;
  number->line = *line;
  number->cursor = *cursor;
  number->type = TOKEN_NUMBER;
  number->value = (char *)malloc(2);
  number->value[0] = *next_character;
  number->value[1] = '\0';
  current_size = 1;

  if (*next_character == '0')
  {
    peek_character = NULL;
    peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (*peek_character == 'X' || *peek_character == 'x')
    {
      deallocate(peek_character);
      character_in_string = NULL;
      character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      (*cursor) += 1;
      append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
      deallocate(character_in_string);

      while (1)
      {
        character_in_string = NULL;
        character_in_string_width = consume(buffer, index, current_character, &character_in_string);
        (*cursor) += 1;
        if (isxdigit(*character_in_string))
        {
          append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
          deallocate(character_in_string);
          continue;
        }
        deallocate(character_in_string);
        break;
      }
    }
    else
    {
      deallocate(peek_character);
    }
  }

  while (1)
  {
    peek_character = NULL;
    peek_character_width = peek(buffer, index, current_character, &peek_character);
    if (peek_character_width == 1 &&
        (isdigit(*peek_character) || *peek_character == '.' || *peek_character == 'f' || *peek_character == 'i'))
    {
      deallocate(peek_character);
      character_in_string = NULL;
      character_in_string_width = consume(buffer, index, current_character, &character_in_string);
      *cursor += 1;
      append_to(&number->value, &current_size, &character_in_string, &character_in_string_width);
      deallocate(character_in_string);
      continue;
    }
    deallocate(peek_character);
    break;
  }

  node = list_node_new(number);
  list_rpush(tokens, node);
}

void parse_punctuation(const char *file_path, unsigned int *line,
                       unsigned int *cursor, char *current_character, list_t *tokens)
{
  /* declarations */
  list_node_t *node;

  if (ispunct(*current_character))
  {
    /* create a "punctuation" token */
    struct token_t *punctuation = (struct token_t *)malloc(sizeof(struct token_t));
    punctuation->file_path = file_path;
    punctuation->line = *line;
    punctuation->cursor = *cursor;
    punctuation->type = TOKEN_PUNCTUATION;
    punctuation->value = (char *)malloc(2);

    /* save current character in punctuation value */
    punctuation->value[0] = (*current_character);
    punctuation->value[1] = '\0';

    /* save punctuation token in linked list */
    node = list_node_new(punctuation);
    list_rpush(tokens, node);
  }
}

/* the main lexer post-processing function */
void lexer_post_process(list_t *tokens)
{
  /* declarations */
  list_node_t *node;
  list_iterator_t *it;

  /* use list_iterator to iterate over list of tokens */
  
  it = list_iterator_new(tokens, LIST_HEAD);
  while ((node = list_iterator_next(it)))
  {
    /* Keep pointers to two consecutive tokens - current and next */
    struct token_t *current_token = ((struct token_t *)node->val);
    struct token_t *next_token = NULL;

    list_node_t *next_node = node->next;
    if (next_node) {
      next_token = ((struct token_t *)next_node->val);
    }

    /* at this point, both current and next token are pointing to something (even NULL) */

    /* 
      I'm going to use process_token and process_token_sequence macros to make this section more
      readable and so I don't have a giant if-else ladder

      process_token does the following:
      (1) call check_and_update_token(...)
      (2) check if the current_token->value is the same as the first argument to process_token
      (3) if it is, we need to reclassify this token as <second argument of process_token>
          e.g., if the current_token value is ',', we re-classify this token as TOKEN_COMMA

      process_token_sequence does the following:
      (1) call check_and_update_token(...)
      (2) check if the current_token->value is the same as the first argument to process_token
      (3) check if the next_token->value is the same as the second argument to process_value_sequence
      (3) if it is, we need to reclassify this token as <third argument of process_value_token>
          e.g., if the current_token value is '>=', we re-classify this token as TOKEN_GREATER_EQUAL
      (4) DELETE the linked list node associated with next_token from tokens before continuing the loop

      Both process_token and process_token_sequence 'continue' the loop if the check in step (2/3) passes
    */

    /* handle two-character operators first */

    /* comparison operators */
    process_token_sequence("=", "=", TOKEN_EQUAL);
    process_token_sequence("!", "=", TOKEN_NOT_EQUAL);
    process_token_sequence(">", "=", TOKEN_GREATER_EQUAL);
    process_token_sequence("<", "=", TOKEN_LESSER_EQUAL);

    /* assignment operators */
    process_token_sequence("+", "=", TOKEN_ADD_ASSIGN);
    process_token_sequence("-", "=", TOKEN_SUBTRACT_ASSIGN);
    process_token_sequence("*", "=", TOKEN_MULTIPLY_ASSIGN);
    process_token_sequence("/", "=", TOKEN_DIVIDE_ASSIGN);
    process_token_sequence("-", "=", TOKEN_MODULUS_ASSIGN);

    /* logical operators */
    process_token_sequence("&", "&", TOKEN_LOGICAL_AND);
    process_token_sequence("!", "!", TOKEN_LOGICAL_OR);

    /* bitwise operators */
    process_token_sequence("<", "<", TOKEN_BITWISE_LEFT_SHIFT);
    process_token_sequence(">", ">", TOKEN_BITWISE_RIGHT_SHIFT);

    /* handle one-character operators */

    /* if the compound versions of the following tokens fail on check, save as follows:*/
    process_token(">", TOKEN_GREATER);
    process_token("<", TOKEN_LESSER);
    process_token("&", TOKEN_BITWISE_AND);
    process_token("|", TOKEN_BITWISE_OR);

    /* arithmetic operators */
    process_token("+", TOKEN_ADD);
    process_token("-", TOKEN_SUBTRACT);
    process_token("*", TOKEN_MULTIPLY);
    process_token("/", TOKEN_DIVIDE);
    process_token("%", TOKEN_MODULUS);
    
    /* delimiters */
    process_token(".", TOKEN_DOT);
    process_token(",", TOKEN_COMMA);
    process_token(":", TOKEN_COLON);
    process_token(";", TOKEN_SEMI_COLON);
    process_token("!", TOKEN_EXCLAMATION);
    process_token("?", TOKEN_QUESTION);

    /* paranthesis, curly braces and square brackets */
    process_token("(", TOKEN_LEFT_PARANTHESIS);
    process_token("{", TOKEN_LEFT_CURLY);
    process_token("[", TOKEN_LEFT_BRACKETS);
    process_token(")", TOKEN_RIGHT_PARANTHESIS);
    process_token("}", TOKEN_RIGHT_CURLY);
    process_token("]", TOKEN_RIGHT_BRACKETS);

    /* bitwise operators */
    process_token("^", TOKEN_BITWISE_XOR);
    process_token("~", TOKEN_BITWISE_ONES_COMPLEMENT);

  }
  deallocate(it);
}

int check_and_update_token(struct token_t * current_token, char * current_token_value,
  int check_next_token, // should next token be considered or is checking current_token enough?
  struct token_t * next_token, char * next_token_value, token new_type, char * new_value)
{
  /* declarations */
  int check_passed;

  check_passed = strequal(current_token->value, current_token_value) && 
                  (check_next_token ? strequal(next_token->value, next_token_value) : 1);

  if (check_passed)
  {
    update_token_type(current_token, new_type);
    update_token_value(current_token, new_value);
    return 1;
  }
  return 0;
}

void update_token_type(struct token_t * current_token, token new_type)
{
  if (!current_token)
    return;
  current_token->type = new_type;
}

void update_token_value(struct token_t * current_token, const char * new_value)
{
  /* declarations */
  size_t i;
  size_t new_value_size;
  char *realloc_token;

  if (!current_token)
    return;

  if (strequal(current_token->value, new_value))
    return;

  new_value_size = strlen(new_value);

  /* reallocate space in current_token->value and copy "==" into it */
  realloc_token = realloc(current_token->value, new_value_size + 1);
  if (!realloc_token)
  {
    fprintf(stderr, "realloc failed!\n");
    exit(EXIT_FAILURE);
  }
  /* reallocation successful */
  current_token->value = realloc_token;

  /* copy value into current_token->value from new_value */
  for (i = 0; i < new_value_size; i++)
    current_token->value[i] = new_value[i];
  current_token->value[new_value_size] = '\0';
}