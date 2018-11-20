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

TEST_CASE("The evaluator can interpret list.enumerate()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = 
    "fruits := [\"apple\", \"banana\", \"grapes\", \"pear\"];"
    "result := [];"
    "for c, value in fruits.enumerate() {"
    "  result.append([c, value]);"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[\"apple\", \"banana\", \"grapes\", \"pear\"]");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[[0, \"apple\"], [1, \"banana\"], [2, \"grapes\"], [3, \"pear\"]]");
}

TEST_CASE("The evaluator can interpret list.enumerate(1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := [\"apple\", \"banana\", \"grapes\", \"pear\"];"
    "result := [];"
    "for c, value in fruits.enumerate(1) {"
    "  result.append([c, value]);"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[\"apple\", \"banana\", \"grapes\", \"pear\"]");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[[1, \"apple\"], [2, \"banana\"], [3, \"grapes\"], [4, \"pear\"]]");
}

TEST_CASE("The evaluator can interpret list.enumerate(start = 1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := [\"apple\", \"banana\", \"grapes\", \"pear\"];"
    "result := [];"
    "for c, value in fruits.enumerate(start = 1) {"
    "  result.append([c, value]);"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[\"apple\", \"banana\", \"grapes\", \"pear\"]");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[[1, \"apple\"], [2, \"banana\"], [3, \"grapes\"], [4, \"pear\"]]");
}

TEST_CASE("The evaluator can interpret tuple.enumerate()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := (\"apple\", \"banana\", \"grapes\", \"pear\");"
    "result := [];"
    "for c, value in fruits.enumerate() {"
    "  result.append((c, value));"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(\"apple\", \"banana\", \"grapes\", \"pear\")");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[(0, \"apple\"), (1, \"banana\"), (2, \"grapes\"), (3, \"pear\")]");
}

TEST_CASE("The evaluator can interpret tuple.enumerate(1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := (\"apple\", \"banana\", \"grapes\", \"pear\");"
    "result := [];"
    "for c, value in fruits.enumerate(1) {"
    "  result.append((c, value));"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(\"apple\", \"banana\", \"grapes\", \"pear\")");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[(1, \"apple\"), (2, \"banana\"), (3, \"grapes\"), (4, \"pear\")]");
}

TEST_CASE("The evaluator can interpret tuple.enumerate(start = 1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := (\"apple\", \"banana\", \"grapes\", \"pear\");"
    "result := [];"
    "for c, value in fruits.enumerate(start = 1) {"
    "  result.append((c, value));"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::TUPLE);
  REQUIRE(result->Inspect() == "(\"apple\", \"banana\", \"grapes\", \"pear\")");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[(1, \"apple\"), (2, \"banana\"), (3, \"grapes\"), (4, \"pear\")]");
}

TEST_CASE("The evaluator can interpret set.enumerate()", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := {\"apple\", \"banana\", \"grapes\", \"pear\"};"
    "result := [];"
    "for c, value in fruits.enumerate() {"
    "  result.append({c, value});"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{\"apple\", \"banana\", \"grapes\", \"pear\"}");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[{0, \"apple\"}, {1, \"banana\"}, {2, \"grapes\"}, {3, \"pear\"}]");
}

TEST_CASE("The evaluator can interpret set.enumerate(1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := {\"apple\", \"banana\", \"grapes\", \"pear\"};"
    "result := [];"
    "for c, value in fruits.enumerate(1) {"
    "  result.append({c, value});"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{\"apple\", \"banana\", \"grapes\", \"pear\"}");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[{1, \"apple\"}, {2, \"banana\"}, {3, \"grapes\"}, {4, \"pear\"}]");
}

TEST_CASE("The evaluator can interpret set.enumerate(start = 1)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "fruits := {\"apple\", \"banana\", \"grapes\", \"pear\"};"
    "result := [];"
    "for c, value in fruits.enumerate(start = 1) {"
    "  result.append({c, value});"
    "}"
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
  ObjectPtr result = environment->Get("fruits");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::SET);
  REQUIRE(result->Inspect() == "{\"apple\", \"banana\", \"grapes\", \"pear\"}");
  result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[{1, \"apple\"}, {2, \"banana\"}, {3, \"grapes\"}, {4, \"pear\"}]");
}

} // namespace walnut