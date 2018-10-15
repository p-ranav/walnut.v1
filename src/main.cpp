#include <lexer.hpp>
#include <parser.hpp>

#include <iostream>
#include <string>
#include <clocale>

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  if (argc == 1)
  {
    while (true)
    {
      std::cout << ">>> ";
      String buffer;
      char c = '\0';
      while (c != '\n') {
        c = std::cin.get();
        buffer += c;
      }
      Lexer lexer("", buffer);
      lexer.Tokenize();

      Parser parser(lexer.tokens);
      parser.ParseProgram();
    }
  }
  else if (argc == 2)
  {
    String filename = argv[1];
    InputFileStream file_stream(filename);
    String buffer = String((EndOfStreamIterator(file_stream)), EndOfStreamIterator());

    Lexer lexer(filename, buffer);
    lexer.Tokenize();

    Parser parser(lexer.tokens);
    parser.ParseProgram();
  }
  return 0;
}