#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

TEST_CASE("The evaluator can interpret string.format() 1", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"[Thread {thread}]::{log_level}::{message}\""
    ".format(thread = 0,"
    "  log_level = \"INFO\","
    "  message = \"Recording started\");"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "[Thread 0]::INFO::Recording started");
}

TEST_CASE("The evaluator can interpret string.format() 2", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"{0}, {world}\".format(\"Hello\", world = \"世界\");"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "Hello, 世界");
}

TEST_CASE("The evaluator can interpret integer.format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"5\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "5");
}

TEST_CASE("The evaluator can interpret double.format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"3.14\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "3.14");
}

TEST_CASE("The evaluator can interpret true.format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"true\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "true");
}

TEST_CASE("The evaluator can interpret false.format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"false\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "false");
}

TEST_CASE("The evaluator can interpret {}.format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"{}\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "{}");
}

TEST_CASE("The evaluator can interpret [].format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"[]\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "[]");
}

TEST_CASE("The evaluator can interpret ().format()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "result := \"()\".format()"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::STRING);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result_string->Value() == "()");
}

} // namespace walnut