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

TEST_CASE("The evaluator can check if a list contains an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 in [1, 2, 3];";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a list contains an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 in [1, 2, 3];";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a list doesn't contain an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 not in [1, 2, 3];";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a list doesn't contain an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 not in [1, 2, 3];";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a string contains a substring", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := \"rice\" in \"salad, pasta, sandwich, pizza, drinks, dessert\";";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a string contains a substring (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := \"pasta\" in \"salad, pasta, sandwich, pizza, drinks, dessert\";";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a string doesn't contain a substring", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := \"rice\" not in \"salad, pasta, sandwich, pizza, drinks, dessert\";";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a string doesn't contain a substring (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := \"pasta\" not in \"salad, pasta, sandwich, pizza, drinks, dessert\";";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a set contains an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 in {1, 2, 3};";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a set contains an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 in {1, 2, 3};";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a set doesn't contain an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 not in {1, 2, 3};";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a set doesn't contain an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 not in {1, 2, 3};";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a tuple contains an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 in (1, 2, 3);";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a tuple contains an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 in (1, 2, 3);";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a tuple doesn't contain an element", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 4 not in (1, 2, 3);";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a tuple doesn't contain an element (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 not in (1, 2, 3);";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can check if a list/set/tuple contains elements (I)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := ((1 in [1, 2, 3]) and (2 in (2, 3, 4)) and (3 not in {4, 5, 6}));";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can check if a list/set/tuple contains elements (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "result := 1 in [1, 2, 3] and 2 in (2, 3, 4) and 3 not in {4, 5, 6};";

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
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

} // namespace walnut