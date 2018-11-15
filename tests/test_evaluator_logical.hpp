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

  TEST_CASE("The evaluator can interpret logical AND expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true and false);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "false");
  }

  TEST_CASE("The evaluator can interpret logical or expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true or false);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "true");
  }

  TEST_CASE("The evaluator can interpret logical 'and not' expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true and not false);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "true");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true or not true and true);"; // (true or (!true and true))

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "true");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions v2", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true or not true and false);"; // (true or (!true and false))

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "true");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions v3", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (true and not true and false);"; // (true and (!true and false))

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "false");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions v4", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (false and false and not true);"; // (false and (false and (not true)))

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "false");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions v5", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := !(true and false);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "true");
  }

  TEST_CASE("The evaluator can interpret logical 'and or not' expressions v6", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := !(true or false);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::BOOLEAN);
    REQUIRE(x->Inspect() == "false");
  }

} // namespace walnut