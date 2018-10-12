#include <lexer.h>

extern const char *const token_strings[]; /* used in lexer_print */

list_t *lexer_tokenize(const char *file_path, long buffer_size, char *buffer)
{
  /* declarations */
  list_t *tokens;
  unsigned int line;
  unsigned int cursor;
  long index;
  char character;
  char *next;
  long next_width;
  struct token_t *eof;
  list_node_t *node;

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
        parse_comments(buffer_size, buffer, file_path, &line, &cursor, &index, &character, tokens);

      /* check if the next character is the start of a number. Consume till end of number */
      if (isdigit(*next))
        parse_number(buffer_size, buffer, file_path, &line, &cursor, &index, &character, next, tokens);

      /* now check if the next character is the start of symbol - identifier or keyword */
      else if (valid_symbol(next_width, next))
        parse_symbol(buffer_size, buffer, file_path, &line, &cursor, &index,
                     &character, next_width, next, tokens);

      /* consume all whitespace */
      else if (whitespace(next_width, next))
        parse_whitespace(buffer_size, buffer, &cursor, &index, &character);

      /* check if the next character is the start of a string literal, e.g., "Hello World" */
      else if (startswith(next, next_width, '\"'))
        parse_string_literal(buffer_size, buffer, file_path, &line, &cursor, &index, &character, tokens);

      /* check if next character is a punctuation. if so, consume 1 character and move on */
      else if (ispunct(*next))
        parse_punctuation(file_path, &line, &cursor, &character, tokens);

      /* if newline is encountered, update line and reset cursor */
      if (startswith(next, next_width, '\n'))
      {
        line += 1;
        cursor = 1;
      }

      /* we've made the most out of 'next' - deallocate it before looping again. */
      deallocate(next);

      continue;
    }
  }

  /* create and save "end of file" token */
  eof = allocate(struct token_t, 1);
  eof->file_path = file_path;
  eof->line = line;
  eof->cursor = cursor;
  eof->type = TOKEN_END_OF_FILE;
  eof->value = allocate(char, 1);
  eof->value[0] = '\0';
  save_token(eof);

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
    const char *token_string = token_strings[token->type];

    /* Log lexer token as JSON */
    printf(
        "{"
        "\"file\": \"%s\","
        "\"line\": %d,"
        "\"cursor\": %d,"
        "\"input\": \"%s\","
        "\"token\": \"%s\""
        "}\n",
        token->file_path,
        token->line,
        token->cursor,
        token->value,
        token_string);
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
  int sequence_length; /* length of UTF-8 sequence starting with current_character */
  int sequence_index;  /* index in the range [0, sequence_length) */

  /* get the width of this unicode character */
  sequence_length = u8_seqlen(current_character);

  /* prepare character array to hold multi-byte character */
  *multi_byte_character = allocate(char, sequence_length + 1);
  memset(*multi_byte_character, '\0', sequence_length);

  /* parse multi-byte unicode character */
  sequence_index = 0;
  while (sequence_index < sequence_length)
  {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';
  /* return the width of the consumed multi-byte character */
  return sequence_length;
}

long peek(char *buffer, long *index, char *current_character, char **multi_byte_character)
{
  /* declarations */
  int sequence_length; /* length of UTF-8 sequence starting with current_character */
  int sequence_index;  /* index in the range [0, sequence_length) */

  /* get the width of this unicode character */
  sequence_length = u8_seqlen(current_character);

  /* prepare character array to hold multi-byte character */
  *multi_byte_character = allocate(char, sequence_length + 1);
  memset(*multi_byte_character, '\0', sequence_length);

  /* parse multi-byte unicode character */
  sequence_index = 0;
  while (sequence_index < sequence_length)
  {
    *current_character = buffer[*index];
    *index += 1;
    sequence_index += 1;
    (*multi_byte_character)[sequence_index - 1] = *current_character;
  }
  (*multi_byte_character)[sequence_index] = '\0';

  /* undo changes to index and current_character */
  *index -= sequence_length;
  (*current_character) = buffer[*index];

  /* return the width of the peek'd multi-byte character */
  return sequence_length;
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

void parse_comments(long buffer_size, char *buffer, const char *file_path, unsigned int *line, unsigned int *cursor, long *index, char *current_character, list_t *tokens)
{
  /* declarations */
  char *next = NULL;
  long next_width;
  list_node_t *node;

  increment_cursor;
  next_width = consume(buffer, index, current_character, &next);
  increment_cursor;

  /* check if next character starts with '/'
     if yes, treat this as the start of a line comment */
  if (startswith(next, next_width, '/'))
  {
    /* loop until end of line comment, i.e., end of line or end of file */
    while (!startswith(next, next_width, 0x0A) && (*index < buffer_size))
    {
      deallocate(next);
      next_width = consume(buffer, index, current_character, &next);
      increment_cursor;
    }
    increment_line;
    reset_cursor;
  }
  else if (startswith(next, next_width, '*'))
  {
    /* this is a block comment
       consume characters till we encounter '*' followed by '/' */
    while (1)
    {
      deallocate(next);
      next_width = consume(buffer, index, current_character, &next);
      increment_cursor;

      if (startswith(next, next_width, EOF))
      {
        fprintf(stderr, "block comment not terminated before end of file\n");
        exit(EXIT_FAILURE);
      }

      if (startswith(next, next_width, 0x0A))
      {
        /* end of line. increment line, reset cursor, and continue */
        increment_line;
        reset_cursor;
        continue;
      }

      if (startswith(next, next_width, '*'))
      {
        /* peek into the next character. We're hoping for '/' to close out the block comment */
        deallocate(next);
        next_width = peek(buffer, index, current_character, &next);

        /* error condition: we reach EOF before the block comment is closed */
        if (startswith(next, next_width, EOF))
        {
          fprintf(stderr, "block comment not terminated before end of file\n");
          exit(EXIT_FAILURE);
        }

        if (startswith(next, next_width, '/'))
        {
          /* peek is a '/' - deallocate and then consume */
          deallocate(next);

          /* consume this character and return */
          consume(buffer, index, current_character, &next);
          increment_cursor;
          deallocate(next);

          consume(buffer, index, current_character, &next);
          increment_cursor;
          deallocate(next);

          return;
        }
        deallocate(next);
      }
    }
  }
  else
  {
    /* create a "punctuation" token */
    struct token_t *punctuation = allocate(struct token_t, 1);
    punctuation->file_path = file_path;
    punctuation->line = *line;
    punctuation->cursor = *cursor;
    punctuation->type = TOKEN_DIVIDE;
    punctuation->value = allocate(char, 2);

    /* save current character in punctuation value */
    punctuation->value[0] = '/';
    punctuation->value[1] = '\0';

    increment_cursor;
    save_token(punctuation);
  }
  deallocate(next);
}

void parse_symbol(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character,
                  long next_character_width, char *next_character, list_t *tokens)
{
  /* declarations */
  long i;
  long current_size;
  char *next;
  long next_width;
  list_node_t *node;
  struct token_t *symbol;

  if (buffer_size == 0)
    return;

  /* create a "symbol" token */
  symbol = allocate(struct token_t, 1);
  symbol->file_path = file_path;
  symbol->line = *line;
  symbol->cursor = *cursor;
  symbol->type = TOKEN_SYMBOL;

  /* allocate sufficient space for storing symbol value */
  symbol->value = allocate(char, next_character_width + 1);
  for (i = 0; i < next_character_width; i++)
  { /* save one character at a time */
    symbol->value[i] = next_character[i];
  }
  symbol->value[next_character_width] = '\0';

  current_size = next_character_width;
  while (1)
  {
    next = NULL;
    next_width = peek(buffer, index, current_character, &next);

    if (valid_symbol(next_width, next))
    {
      /* consume next_width bytes */
      deallocate(next);

      next_width = consume(buffer, index, current_character, &next);

      /* since we treat this as a single character, update cursor by 1 */
      increment_cursor;

      /* reallocate space in symbol->value and copy this next
         the way this is done here is probably not efficient
         I'm reallocating after each multi-byte character is consumed */
      append_to(&symbol->value, &current_size, &next, &next_width);

      deallocate(next);

      /* continue to next character */
      continue;
    }

    deallocate(next);

    break;
  }
  increment_cursor;
  save_token(symbol);
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
               (character >= '0' && character <= '9') ||
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
  char *expanded_lhs = realloc(*lhs, *lhs_size + *rhs_size + 1);
  if (!expanded_lhs)
  {
    fprintf(stderr, "realloc failed!\n");
    exit(EXIT_FAILURE);
  }
  *lhs = expanded_lhs;

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
  /* declarations */
  char *next;
  long next_width;

  increment_cursor; /* increment cursor since current_character = whitespace */

  if (buffer_size == 0)
    return;

  while (1)
  {
    /* loop here until we stop encountering 'space' characters */
    next = NULL;
    next_width = peek(buffer, index, current_character, &next);
    if (whitespace(next_width, next))
    {
      deallocate(next);
      next_width = consume(buffer, index, current_character, &next);
      deallocate(next);
      increment_cursor;
      continue;
    }
    deallocate(next);
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
  char *next;
  long next_width;
  list_node_t *node;
  struct token_t *string;

  if (buffer_size == 0)
    return;

  /* create a "string" token */
  string = allocate(struct token_t, 1);
  string->file_path = file_path;
  string->line = *line;
  string->cursor = *cursor;
  string->type = TOKEN_STRING_LITERAL;

  string->value = NULL;
  current_size = 0;
  while (1)
  {
    /* loop till we encounter the closing double quotes */
    next = NULL;
    next_width = peek(buffer, index, current_character, &next);
    increment_cursor;

    if (startswith(next, next_width, '\\'))
    {
      deallocate(next);

      /* escape sequence */
      next = NULL;
      next_width = consume(buffer, index, current_character, &next);
      if (startswith(next, next_width, '\"') ||
          startswith(next, next_width, '\\'))
      {
        deallocate(next);

        next_width = consume(buffer, index, current_character, &next);
        increment_cursor;

        /* realloc and add next to string->value */
        append_to(&string->value, &current_size, &next, &next_width);

        deallocate(next);

        continue;
      }

      /* end of line or end of file before the closing quotes */
      if (startswith(next, next_width, 0x0A) ||
          startswith(next, next_width, EOF))
      {
        deallocate(next);
        /* TODO: report this error a little better */
        fprintf(stderr, "EOL/EOF encountered before closing literal quotes\n");
        exit(EXIT_FAILURE);
      }

      /* realloc and add next to string->value */
      append_to(&string->value, &current_size, &next, &next_width);

      deallocate(next);
      continue;
    }

    /* Add to string literal if not closing quotes or end of file */
    if (!startswith(next, next_width, '\"') &&
        !startswith(next, next_width, EOF))
    {
      deallocate(next);

      /* realloc and add next to string->value */
      next = NULL;
      next_width = consume(buffer, index, current_character, &next);
      append_to(&string->value, &current_size, &next, &next_width);

      deallocate(next);
      continue;
    }

    /* end of line or end of file before the closing quotes */
    if (startswith(next, next_width, 0x0A) ||
        startswith(next, next_width, EOF))
    {
      /* TODO: report this error a little better */
      fprintf(stderr, "EOL/EOF encountered before closing literal quotes\n");
      exit(EXIT_FAILURE);
    }
    /* consume the closing double quotes */
    deallocate(next);

    next = NULL;
    consume(buffer, index, current_character, &next);

    deallocate(next);
    break;
  }
  increment_cursor;
  save_token(string);
}

void parse_number(long buffer_size, char *buffer, const char *file_path, unsigned int *line,
                  unsigned int *cursor, long *index, char *current_character,
                  char *next_character, list_t *tokens)
{
  /* declarations */
  long current_size;
  char *next;
  long next_width;
  list_node_t *node;
  struct token_t *number;

  if (buffer_size == 0)
    return;

  /* create a "punctuation" token */
  number = allocate(struct token_t, 1);
  number->file_path = file_path;
  number->line = *line;
  number->cursor = *cursor;
  number->type = TOKEN_NUMBER;
  number->value = allocate(char, 2);
  number->value[0] = *next_character;
  number->value[1] = '\0';
  current_size = 1;

  if (*next_character == '0')
  {
    next = NULL;
    next_width = peek(buffer, index, current_character, &next);
    if (*next == 'X' || *next == 'x')
    {
      deallocate(next);
      next = NULL;
      next_width = consume(buffer, index, current_character, &next);
      increment_cursor;
      append_to(&number->value, &current_size, &next, &next_width);
      deallocate(next);

      while (1)
      {
        next = NULL;
        next_width = consume(buffer, index, current_character, &next);
        increment_cursor;
        if (isxdigit(*next))
        {
          append_to(&number->value, &current_size, &next, &next_width);
          deallocate(next);
          continue;
        }
        deallocate(next);
        break;
      }
    }
    else
      deallocate(next);
  }

  while (1)
  {
    next = NULL;
    next_width = peek(buffer, index, current_character, &next);
    if (next_width == 1 &&
        (isdigit(*next) || *next == '.' || *next == 'f' || *next == 'i'))
    {
      deallocate(next);
      next = NULL;
      next_width = consume(buffer, index, current_character, &next);
      increment_cursor;
      append_to(&number->value, &current_size, &next, &next_width);
      deallocate(next);
      continue;
    }
    deallocate(next);
    break;
  }
  increment_cursor;
  save_token(number);
}

void parse_punctuation(const char *file_path, unsigned int *line,
                       unsigned int *cursor, char *current_character, list_t *tokens)
{
  /* declarations */
  list_node_t *node;

  if (ispunct(*current_character))
  {
    /* create a "punctuation" token */
    struct token_t *punctuation = allocate(struct token_t, 1);
    punctuation->file_path = file_path;
    punctuation->line = *line;
    punctuation->cursor = *cursor;
    punctuation->type = TOKEN_PUNCTUATION;
    punctuation->value = allocate(char, 2);

    /* save current character in punctuation value */
    punctuation->value[0] = (*current_character);
    punctuation->value[1] = '\0';

    increment_cursor;
    save_token(punctuation);
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
    if (next_node)
    {
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
    process_token_sequence("%", "=", TOKEN_MODULUS_ASSIGN);

    /* logical operators */
    process_token_sequence("&", "&", TOKEN_LOGICAL_AND);
    process_token_sequence("!", "!", TOKEN_LOGICAL_OR);

    /* bitwise operators */
    process_token_sequence("<", "<", TOKEN_BITWISE_LEFT_SHIFT);
    process_token_sequence(">", ">", TOKEN_BITWISE_RIGHT_SHIFT);

    /* arrow operator */
    process_token_sequence("-", ">", TOKEN_ARROW);

    /* handle one-character operators */

    /* keywords and operators for type inference */
    process_token("var", TOKEN_VAR);

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

    /* assignment operator */
    process_token("=", TOKEN_ASSIGN);

    /* keywords */
    process_token("true", TOKEN_TRUE);
    process_token("false", TOKEN_FALSE);
    process_token_sequence("else", "if", TOKEN_ELSE_IF);
    process_token("if", TOKEN_IF);
    process_token("else", TOKEN_ELSE);
    process_token("while", TOKEN_WHILE);
    process_token("for", TOKEN_FOR);
    process_token("function", TOKEN_FUNCTION);
    process_token("return", TOKEN_RETURN);
    process_token("is", TOKEN_IS);
    process_token("in", TOKEN_IN);
    process_token("with", TOKEN_WITH);
    process_token("continue", TOKEN_CONTINUE);
    process_token("break", TOKEN_BREAK);
    process_token("try", TOKEN_TRY);
    process_token("catch", TOKEN_CATCH);
    process_token("finally", TOKEN_FINALLY);
    process_token("pass", TOKEN_PASS);
    process_token("from", TOKEN_FROM);
    process_token("import", TOKEN_IMPORT);

    /* Unicode characters */
    process_token("ƒ", TOKEN_FUNCTION);      /* "ƒ" (U+0192) */
    process_token("𝑓", TOKEN_FUNCTION);      /* "𝑓" (U+1D453) */
    process_token("＝", TOKEN_EQUAL);        /* "＝" (U+FF1D) */
    process_token("≥", TOKEN_GREATER_EQUAL); /* "≥" (U+2265) */
    process_token("≤", TOKEN_LESSER_EQUAL);  /* "≤" (U+2264) */
    process_token("≠", TOKEN_NOT_EQUAL);     /* "≠" (U+2260) */
    process_token("⋅", TOKEN_MULTIPLY);      /* "⋅" (U+22C5) Middle-dot */
    process_token("•", TOKEN_MULTIPLY);      /* "•" (U+2022) Bullet */
    process_token("×", TOKEN_MULTIPLY);      /* "×" (U+00D7) Multiplication */

    /* handle numbers */
    if (current_token->type == TOKEN_NUMBER)
    {
      if (strstr(current_token->value, ".") != NULL && strstr(current_token->value, "f") != NULL)
      {
        current_token->type = TOKEN_FLOAT;
      }
      else if (strstr(current_token->value, ".") != NULL)
      {
        current_token->type = TOKEN_DOUBLE;
      }
      else
        current_token->type = TOKEN_INTEGER;
    }
  }
  deallocate(it);
}

int check_and_update_token(struct token_t *current_token, char *current_token_value,
                           int check_next_token, /* should next token be considered or is checking current_token enough? */
                           struct token_t *next_token, char *next_token_value, token new_type, char *new_value)
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

void update_token_type(struct token_t *current_token, token new_type)
{
  if (!current_token)
    return;
  current_token->type = new_type;
}

void update_token_value(struct token_t *current_token, const char *new_value)
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