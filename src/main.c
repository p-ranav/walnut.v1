#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    // TODO: implement REPL
    printf("Usage: ./carbon <filename>");
  }
  else if (argc == 2) {

    // set single locale for all purposes
    setlocale(LC_ALL, "");

    // TODO: Allow filenames with unicode characters
    // e.g., filename with multi-byte chinese characters
    const char * filename = argv[1];



  }

  return 0;
}