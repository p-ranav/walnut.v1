#include <file.h>
#include <macros.h>
#include <lexer.h>

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    // TODO: implement REPL
    trace("Usage: ./carbon <filename>");
  }
  else if (argc == 2) {

    // set single locale for all purposes
    setlocale(LC_ALL, "");

    // TODO: Allow filenames with unicode characters
    // e.g., filename with multi-byte chinese characters
    const char * file_path = argv[1];

    // Read from file and retrieve buffer of characters
    char * buffer = NULL;
    long file_size = read_file(file_path, &buffer);
    trace("%s (%ld bytes)\n", file_path, file_size);

    // Tokenize the buffer of characters
    tokenize(file_size, buffer);

  }

  return 0;
}