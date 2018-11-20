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

TEST_CASE("The evaluator can interpret array indexing", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [1, 2, 3, 4, 5]; x[0] = -1;";

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
  REQUIRE(result->Inspect() == "[-1, 2, 3, 4, 5]");
}

TEST_CASE("The evaluator can interpret array indexing in while loops", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "y := [1, 2, 3, 4, 5];"
    "i := 0;"
    "while i < y.length() {"
    "  y[i] = y[i] * -1;"
    "  i = i + 1;"
    "}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[-1, -2, -3, -4, -5]");
}

TEST_CASE("The evaluator can interpret array indexing in nested lists", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [[1, 2], [3, 4], 5];"
    "y := x[0];"
    "z := x[1];"
    "a := x[2];"
    "b := x[0][0];"
    "c := x[0][1];"
    "d := x[1][0];"
    "e := x[1][1];"
    "f := x;"
    "f[0] = [-1, -2];";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("y");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[1, 2]");
  result = environment->Get("z");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[3, 4]");
  result = environment->Get("a");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "5");
  result = environment->Get("b");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "1");
  result = environment->Get("c");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "2");
  result = environment->Get("d");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "3");
  result = environment->Get("e");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "4");
  result = environment->Get("f");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[[-1, -2], [3, 4], 5]");
}

} // namespace walnut