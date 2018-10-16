#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>

#include <iostream>
#include <string>
#include <clocale>

void InterpretBuffer(StringConstRef filename, String buffer, EnvironmentPtr environment)
{
  Lexer lexer("", buffer);
  lexer.Tokenize();

  Parser parser(lexer.tokens);
  parser.ParseProgram();

  Evaluator evaluator;
  for (auto& statement : parser.statements)
  {
    ObjectPtr result = evaluator.Eval(statement, environment);
    String inspect = result->Inspect();
    if (inspect != "")
      std::cout << result->Inspect() << std::endl;
    if (result->type == ObjectType::RETURN)
      break;
  }
  lexer.tokens.clear();
  parser.statements.clear();
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
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
      buffer += ";";
      InterpretBuffer("", buffer, environment);
    }
  }
  else if (argc == 2)
  {
    String filename = argv[1];
    InputFileStream file_stream;
    String buffer;
    try
    {
      file_stream = InputFileStream(filename);
      buffer = String((EndOfStreamIterator(file_stream)), EndOfStreamIterator());
    }
    catch (std::exception)
    {
      std::cout << "error: failed to open " << filename << std::endl;
    }
    InterpretBuffer(filename, buffer, environment);
    file_stream.close();
  }
  environment->store.clear();
  return 0;
}