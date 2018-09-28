#include <file.h>
#include <macros.h>
#include <lexer.h>

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    /* TODO: implement REPL */
    trace("Usage: ./carbon <filename>");
  }
  else if (argc == 2) {

    /* Declarations */
    const char * file_path;
    list_t * tokens;
    char * buffer;
    long file_size;

    /* set single locale for all purposes */
    setlocale(LC_ALL, "");

    /* TODO: Allow filenames with unicode characters */
    /* e.g., filename with multi-byte chinese characters */
    file_path = argv[1];

    /* Read from file and retrieve buffer of characters */
    buffer = NULL;
    file_size = read_file(file_path, &buffer);
    trace("%s (%ld bytes)\n", file_path, file_size);

    /* Tokenize the buffer of characters */
    tokens = tokenize(file_path, file_size, buffer);

    /* Print lexer tokens */
    print_tokens(tokens);

    /* Delete lexer tokens */
    delete_tokens(tokens);

    /* Delete original file buffer */
    free(buffer);
  }

  return 0;
}