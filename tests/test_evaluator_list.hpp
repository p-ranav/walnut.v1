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

  TEST_CASE("The evaluator can interpret empty lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[]");
  }

  TEST_CASE("The evaluator can interpret empty lists (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [,];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[]");
  }

  TEST_CASE("The evaluator can interpret single-valued lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [\"apples\",];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[\"apples\"]");
  }

  TEST_CASE("The evaluator can interpret character lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ['a', 'p', 'p', 'l', 'e', 's'];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "['a', 'p', 'p', 'l', 'e', 's']");
  }

  TEST_CASE("The evaluator can interpret lists and grouped expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1 + 2), (3 + 4)];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[3, 7]");
  }

  TEST_CASE("The evaluator can interpret simple lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 3.14, \"Hello\"];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 3.14, \"Hello\"]");
  }

  TEST_CASE("The evaluator can interpret nested lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]], {10, 11}];";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}]");
  }

  TEST_CASE("Lists are mutable", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "x := [1, 3.14, \"Hello\"];"
      "x[0] = 3;"
      "y := x";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 3.14, \"Hello\"]");
    evaluator.Eval(parser.statements[1], environment);
    ObjectPtr y = evaluator.Eval(parser.statements[2], environment);
    REQUIRE(y->type == ObjectType::ARRAY);
    REQUIRE(y->Inspect() == "[3, 3.14, \"Hello\"]");
  }

  TEST_CASE("Lists can be mutated under all scenarios", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 2, [3, 4, 5]];"
      "x[2][0] = -3;"
      "y := x;";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 2, [3, 4, 5]]");
    evaluator.Eval(parser.statements[1], environment);
    ObjectPtr y = evaluator.Eval(parser.statements[2], environment);
    REQUIRE(y->type == ObjectType::ARRAY);
    REQUIRE(y->Inspect() == "[1, 2, [-3, 4, 5]]");
  }

  TEST_CASE("Lists can be iterated with range-based for loops", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "thislist := [\"apple\", \"banana\", \"cherry\"];"
      "y := [];"
      "for x in thislist { y.append(x) }"
      "z := y;";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[\"apple\", \"banana\", \"cherry\"]");
    evaluator.Eval(parser.statements[1], environment);
    evaluator.Eval(parser.statements[2], environment);
    ObjectPtr y = evaluator.Eval(parser.statements[3], environment);
    REQUIRE(y->type == ObjectType::ARRAY);
    REQUIRE(y->Inspect() == "[\"apple\", \"banana\", \"cherry\"]");
  }

} // namespace walnut