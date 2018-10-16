#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>

#include <iostream>
#include <string>
#include <clocale>

void Interpret(String filename, String buffer)
{
  Lexer lexer("", buffer);
  lexer.Tokenize();

  Parser parser(lexer.tokens);
  parser.ParseProgram();

  Evaluator evaluator;
  for (auto& statement : parser.statements)
  {
    ObjectPtr result = evaluator.Eval(statement);
    std::cout << result->Inspect() << std::endl;
  }

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