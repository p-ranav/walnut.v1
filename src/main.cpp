#include <lexer.hpp>
#include <parser.hpp>

#include <iostream>
#include <string>
#include <clocale>

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    std::cerr << "Usage: ./ulang <filename>" << std::endl;
    return 0;
  }
  else if (argc == 2)
  {
    setlocale(LC_ALL, "");

    std::string filename = argv[1];
    lexer::lexer lexer;
    lexer.tokenize(filename);
    parser::parser parser(lexer.tokens);

  }
  return 0;
}