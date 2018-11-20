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

TEST_CASE("The evaluator can interpret list.reduce(func) without initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "15");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, 10);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "25");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, initial_value = 5);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "20");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with negative initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, initial_value = -15);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "0");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) without initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "15");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, 10);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "25");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, initial_value = 5);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "20");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with negative initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, initial_value = -15);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "0");
}

TEST_CASE("The evaluator can interpret set.reduce(func) without initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "15");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with initial value", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, 10);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "25");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, initial_value = 5);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "20");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with negative initial value kwarg", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, initial_value = -15);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "0");
}

TEST_CASE("The evaluator can interpret list.reduce(func) without initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1.0, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1.00, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "15.00");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, 10.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "25.00");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, initial_value = 5.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "20.00");
}

TEST_CASE("The evaluator can interpret list.reduce(func) with negative initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.reduce(function(i, j) { i + j }, initial_value = -15.00);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2, 3, 4, 5]");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "0.00");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) without initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3.0, 4, 5); y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3.00, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "15.00");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, 10.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "25.00");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, initial_value = 5.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "20.00");
}

TEST_CASE("The evaluator can interpret tuple.reduce(func) with negative initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.reduce(function(i, j) { i + j }, initial_value = -15.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 2, 3, 4, 5)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "0.00");
}

TEST_CASE("The evaluator can interpret set.reduce(func) without initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5.5}; y := x.reduce(function(i, j) { i + j });";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5.50}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "15.50");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with initial value (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, 10.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "25.00");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, initial_value = 5.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "20.00");
}

TEST_CASE("The evaluator can interpret set.reduce(func) with negative initial value kwarg (double)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := {1, 2, 3, 4, 5}; y := x.reduce(function(i, j) { i + j }, initial_value = -15.0);";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("x");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{1, 2, 3, 4, 5}");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::DOUBLE);
  REQUIRE(result->Inspect() == "0.00");
}

} // namespace walnut