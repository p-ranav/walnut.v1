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

  TEST_CASE("The evaluator can interpret integer range starting with 0", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := range(8);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::RANGE);
    REQUIRE(x->Inspect() == "[0.000000, 1.000000, ..., 8.000000)");
  }

  TEST_CASE("The evaluator can construct list(range(8))", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := list(range(8));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[0, 1, 2, 3, 4, 5, 6, 7]");
  }

  TEST_CASE("The evaluator can interpret integer range", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := range(1, 8);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::RANGE);
    REQUIRE(x->Inspect() == "[1.000000, 2.000000, ..., 8.000000)");
  }

  TEST_CASE("The evaluator can construct list(range(1, 8))", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := list(range(1, 8));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 2, 3, 4, 5, 6, 7]");
  }

  TEST_CASE("The evaluator can interpret integer range with step", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := range(1, 20, 0.5);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::RANGE);
    REQUIRE(x->Inspect() == "[1.000000, 1.500000, ..., 20.000000)");
  }

  TEST_CASE("The evaluator can construct list(range(1, 10, 0.5))", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := list(range(1, 10, 0.5));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1.00, 1.50, 2.00, 2.50, 3.00, 3.50, 4.00, 4.50, 5.00, 5.50, 6.00, 6.50, 7.00, 7.50, 8.00, 8.50, 9.00, 9.50]");
  }

  TEST_CASE("The evaluator can interpret integer range with negative end", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := range(0, -20);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::RANGE);
    REQUIRE(x->Inspect() == "[0.000000, -1.000000, ..., -20.000000)");
  }

  TEST_CASE("The evaluator can construct list(range(0, -5))", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := list(range(0, -5));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[0, -1, -2, -3, -4]");
  }

  TEST_CASE("The evaluator can interpret integer range with negative end and step", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := range(0, -20, -0.5);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::RANGE);
    REQUIRE(x->Inspect() == "[0.000000, -0.500000, ..., -20.000000)");
  } 

  TEST_CASE("The evaluator can construct list(range(0, -5, -0.5))", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := list(range(0, -5, -0.5));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[0.00, -0.50, -1.00, -1.50, -2.00, -2.50, -3.00, -3.50, -4.00, -4.50]");
  }

}