#include <lexer.hpp>
#include <parser.hpp>

#include <iostream>
#include <string>
#include <clocale>

void Interpret(String filename, String buffer)
{
  Lexer lexer("", buffer);
  lexer.Tokenize();

  Parser parser(lexer.tokens);
  parser.ParseProgram();
}

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
      Interpret("", buffer);
    }
  }
  else if (argc == 2)
  {
    String filename = argv[1];
    InputFileStream file_stream(filename);
    String buffer = String((EndOfStreamIterator(file_stream)), EndOfStreamIterator());
    Interpret(filename, buffer);
  }
  return 0;
}