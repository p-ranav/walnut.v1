#include <lexer.hpp>

#include <iostream>
#include <string>
#include <clocale>

int main(int argc, char *argv[])
{

  if (argc == 1)
  {
    /* report usage */
    std::cerr << "Usage: ./ulang <filename>" << std::endl;
    return 0;
  }
  else if (argc == 2)
  {

    /* set single locale for all purposes */
    setlocale(LC_ALL, "");

    /* TODO: Allow filenames with unicode characters */
    /* e.g., filename with multi-byte chinese characters */
    std::string file_path = argv[1];

    lexer::lexer lexer; /* lol */

    /* Tokenize the buffer of characters */
    lexer.tokenize(file_path);
  }

  return 0;
}