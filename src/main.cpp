#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>

#include <iostream>
#include <string>
#include <clocale>

enum InterpreterMode
{
  READ_EVAL_PRINT,
  READ_FROM_FILE
};

void InterpretBuffer(InterpreterMode mode, StringConstRef filename, String buffer, EnvironmentPtr environment)
{
  Lexer lexer(filename, buffer);
  lexer.Tokenize();

  Parser parser(lexer.tokens);
  parser.ParseProgram();

  Evaluator evaluator;
  for (auto &statement : parser.statements)
  {
    ObjectPtr result = evaluator.Eval(statement, environment);
    String inspect = result->Inspect();
    if (mode == READ_EVAL_PRINT && inspect != "")
      std::cout << inspect << std::endl;
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
      while (c != '\n')
      {
        c = std::cin.get();
        buffer += c;
      }
      buffer += ";";
      InterpretBuffer(READ_EVAL_PRINT, "", buffer, environment);
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
    if (buffer == "")
    {
      std::cout << filename << " is not a valid program" << std::endl;
    }
    InterpretBuffer(READ_FROM_FILE, filename, buffer, environment);
    file_stream.close();
  }
  environment->store.clear();
  return 0;
}