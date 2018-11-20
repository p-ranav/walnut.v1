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

TEST_CASE("The evaluator can interpret if (true) expressions", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := null;"
    "if (true and (true or false)) {"
    "  x = true;"
    "}"
    "else {"
    "  x = false;"
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
  ObjectPtr result = environment->Get("x");
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "true");
}

TEST_CASE("The evaluator can interpret if (false) expressions", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := null;"
    "if (false and (true or false)) {"
    "  x = true;"
    "}"
    "else {"
    "  x = false;"
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
  ObjectPtr result = environment->Get("x");
  REQUIRE(result->type == ObjectType::BOOLEAN);
  REQUIRE(result->Inspect() == "false");
}

TEST_CASE("The evaluator can interpret beer bottles", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "x := [];"
    "for i in range(99, 0, -1) {"
    "  if i == 1 {"
    "    x.append(\"1 bottle of beer\");"
    "  }"
    "  else if i == 2 {"
    "    x.append(\"2 more bottles of beer\");"
    "  }"
    "  else {"
    "    if x.length() == 0 {"
    "      x.append(\"{0}\".format(i) + \" bottles of beer on the wall\");"
    "    }"
    "    else {"
    "      x[0] = \"{0}\".format(i) + \" bottles of beer on the wall\";"
    "    }"
    "  }"
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
  ObjectPtr result = environment->Get("x");
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[\"3 bottles of beer on the wall\", \"2 more bottles of beer\", \"1 bottle of beer\"]");
}

} // namespace walnut