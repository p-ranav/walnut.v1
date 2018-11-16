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

  TEST_CASE("The evaluator can insert into empty lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].insert(0, 1);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1]");
  }

  TEST_CASE("The evaluator can insert into empty lists (index out of range)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].insert(10, 1);"; // index out of range = append

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1]");
  }

  TEST_CASE("The evaluator can insert into simple lists (middle)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 3].insert(1, 2);"; // index out of range = append

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 2, 3]");
  }

  TEST_CASE("The evaluator can insert into simple lists (end)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 3].insert(2, 2);"; // index out of range = append

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 3, 2]");
  }

  TEST_CASE("The evaluator can insert into simple lists (beginning)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 2].insert(0, 0);"; // index out of range = append

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[0, 1, 2]");
  }

  TEST_CASE("The evaluator can insert into empty tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().insert(0, 1);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1)");
  }

  TEST_CASE("The evaluator can insert into empty tuples (index out of range)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().insert(10, 1);"; // index out of range = append

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1)");
  }

  TEST_CASE("The evaluator can insert into simple tuples (middle)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (1, 3).insert(1, 2);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1, 2, 3)");
  }

  TEST_CASE("The evaluator can insert into simple tuples (end)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (1, 3).insert(2, 2);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1, 3, 2)");
  }

  TEST_CASE("The evaluator can insert into simple tuples (beginning)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (1, 2).insert(0, 0);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(0, 1, 2)");
  }

  TEST_CASE("The evaluator can insert into dictionaries", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {}.insert(\"a\", 15);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::HASH);
    REQUIRE(x->Inspect() == "{\"a\" : 15}");
  }

  TEST_CASE("The evaluator can chain insert calls", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {}.insert(\"a\", 15).insert(\"pi\", 3.14);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::HASH);
    REQUIRE(x->Inspect() == "{\"a\" : 15, \"pi\" : 3.14}");
  }

  TEST_CASE("The evaluator will do nothing if key being inserted already exists in dictionary", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {}.insert(\"pi\", 15).insert(\"pi\", 20);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::HASH);
    REQUIRE(x->Inspect() == "{\"pi\" : 15}");
  }

} // namespace walnut