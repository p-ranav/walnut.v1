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

void InterpretBuffer(InterpreterMode mode, walnut::StringConstRef filename, walnut::String buffer, walnut::EnvironmentPtr environment)
{
  walnut::Lexer lexer(filename, buffer);
  lexer.Tokenize();

  walnut::Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();

  walnut::Evaluator evaluator;
  for (auto &statement : parser.statements)
  {
    walnut::ObjectPtr result = evaluator.Eval(statement, environment);
    walnut::String inspect = result->Inspect();
    if (mode == READ_EVAL_PRINT && inspect != "")
      std::cout << inspect << std::endl;
    if (result->type == walnut::ObjectType::RETURN)
      break;
  }
  lexer.tokens.clear();
  parser.statements.clear();
}

int main(int argc, char *argv[])
{

  setlocale(LC_ALL, "");
  walnut::EnvironmentPtr environment = std::make_shared<walnut::Environment>();
  if (argc == 1)
  {
    while (true)
    {
      std::cout << ">>> ";
      walnut::String buffer;
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
    walnut::String filename = argv[1];
    walnut::InputFileStream file_stream;
    walnut::String buffer;
    try
    {
      file_stream = walnut::InputFileStream(filename);
      buffer = walnut::String((walnut::EndOfStreamIterator(file_stream)), walnut::EndOfStreamIterator());
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