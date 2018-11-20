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

TEST_CASE("The evaluator can interpret list.filter(func)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.filter(function(i) { i % 2 == 0 });";

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
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[2, 4]");
}

TEST_CASE("The evaluator can interpret list.filter(func) odd", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; y := x.filter(function(i) { i % 2 != 0 });";

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
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 3, 5]");
}

TEST_CASE("The evaluator can interpret tuple.filter(func)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.filter(function(i) { i % 2 == 0 });";

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
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(2, 4)");
}

TEST_CASE("The evaluator can interpret tuple.filter(func) odd", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := (1, 2, 3, 4, 5); y := x.filter(function(i) { i % 2 != 0 });";

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
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(1, 3, 5)");
}

TEST_CASE("The evaluator can interpret range.filter(func)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := range(6); y := x.filter(function(i) { i % 2 == 0 });";

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
  REQUIRE(result->type == ObjectType::RANGE);
  REQUIRE(result->Inspect() == "[0.000000, 1.000000, ..., 6.000000)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[0, 2, 4]");
}

TEST_CASE("The evaluator can interpret range.filter(func) odd", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := range(6); y := x.filter(function(i) { i % 2 != 0 });";

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
  REQUIRE(result->type == ObjectType::RANGE);
  REQUIRE(result->Inspect() == "[0.000000, 1.000000, ..., 6.000000)");
  result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 3, 5]");
}

} // namespace walnut