#include <file.h>
#include <macros.h>
#include <lexer.h>
#include <parser.h>
#include <evaluator.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[])
{

  if (argc == 1)
  {
    /* report usage */
    fprintf(stderr, "Usage: ./carbin <filename>\n");
    exit(EXIT_FAILURE);
  }
  else if (argc == 2)
  {

    /* Declarations */
    const char *file_path;
    list_t *tokens;
    char *buffer;
    long file_size;
    struct parser_t *parser;
    list_node_t *statement;
    list_iterator_t *it;
    object * eval_result;

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
    /* lexer_print(tokens); */

    /* Parse program */
    parser = parse(tokens);

    /* eval parsed statements */
    it = list_iterator_new(parser->statements, LIST_HEAD);
    while ((statement = list_iterator_next(it)))
    {
      /* get pointer to token and print token type and value */
      node *ast_node = ((node *)statement->val);

      /* print AST node */
      node_print(ast_node);

      /* eval AST node */
      eval_result = eval(ast_node);

      /* print result after evaluation */
      printf(" = %s\n", object_inspect(eval_result));

    }
    deallocate(it);

    /* Delete parsed AST nodes */
    parser_destruct(parser);

    /* Delete lexer tokens */
    lexer_destroy(tokens);

    /* Delete original file buffer */
    free(buffer);
  }

  return 0;
}