#include <file.h>
#include <macros.h>
#include <lexer.h>
#include <parser.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{

  if (argc == 1)
  {
    /* declarations */
    int character;
    char * buffer;
    size_t buffer_size;
    char * expanded_buffer;
    list_t *tokens;
    struct parser_t *parser;

    while (1)
    {

      /* Initializations */
      buffer = (char *)malloc(2);
      buffer[0] = '0';
      buffer[1] = '\0';
      buffer_size = 0;

      /* prompt */
      printf(">>> ");

      /* Start reading characters */
      while ((character = fgetc(stdin)) != EOF)
      {
        if (character == '\n')
          break;
        else if (buffer_size == 0)
        {
          buffer_size += 1;
          buffer[buffer_size - 1] = character;
        }
        else
        {
          buffer_size += 1;
          expanded_buffer = realloc(buffer, buffer_size);
          if (!expanded_buffer)
          {
            printf("error: realloc failed!\n");
            exit(EXIT_FAILURE);
          }
          buffer = expanded_buffer;
          buffer[buffer_size - 1] = character;
          buffer[buffer_size] = '\0';
        }
      }

      /* Tokenize the buffer of characters */
      tokens = lexer_tokenize("", strlen(buffer), buffer);

      /* post-processing step in lexical analysis */
      lexer_post_process(tokens);

      /* Print lexer tokens */
      lexer_print(tokens);

      /* Parse program */
      parser = parse(tokens);

      /* print statements */
      parser_print(parser);

      /* Delete parsed AST nodes */
      parser_destruct(parser);

      /* Delete lexer tokens */
      lexer_destroy(tokens);

      /* Delete original file buffer */
      /* TODO: figure out why free(buffer) crashes */

    }
  }
  else if (argc == 2)
  {

    /* Declarations */
    const char *file_path;
    list_t *tokens;
    char *buffer;
    long file_size;
    struct parser_t *parser;

    /* set single locale for all purposes */
    setlocale(LC_ALL, "");

    /* TODO: Allow filenames with unicode characters */
    /* e.g., filename with multi-byte chinese characters */
    file_path = argv[1];

    /* Read from file and retrieve buffer of characters */
    buffer = NULL;
    file_size = read_file(file_path, &buffer);

    /* Tokenize the buffer of characters */
    tokens = lexer_tokenize(file_path, file_size, buffer);

    /* post-processing step in lexical analysis */
    lexer_post_process(tokens);

    /* Print lexer tokens */
    lexer_print(tokens);

    /* Parse program */
    parser = parse(tokens);

    /* print statements */
    parser_print(parser);

    /* Delete parsed AST nodes */
    parser_destruct(parser);

    /* Delete lexer tokens */
    lexer_destroy(tokens);

    /* Delete original file buffer */
    free(buffer);
  }

  return 0;
}