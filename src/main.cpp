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
    Lexer lexer;
    lexer.Tokenize(filename);
    Parser parser(lexer.tokens);
    parser.ParseProgram();
  }
  return 0;
}