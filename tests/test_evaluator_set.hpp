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

  TEST_CASE("The evaluator can interpret empty sets (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{}");
  }

  TEST_CASE("The evaluator can interpret single-valued sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {\"apples\",};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{\"apples\"}");
  }

  TEST_CASE("The evaluator can interpret character sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {'a', 'p', 'p', 'l', 'e', 's'};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{'a', 'p', 'l', 'e', 's'}");
  }

  TEST_CASE("The evaluator can interpret integer sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 2, 3, 4, 5, 6};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 2, 3, 4, 5, 6}");
  }

  TEST_CASE("The evaluator can interpret integer sets with duplicates", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 3, 4, 5, 6};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 2, 3, 4, 5, 6, 7, 8, 9}");
  }

  TEST_CASE("The evaluator can interpret heterogeneous sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 3.14, 3.14, 5, 3.1415, 6, \"H\", 'c', function(a) { a }};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 3.14, 5, 6, \"H\", 'c', function(a) { a; }}");
  }

  TEST_CASE("The evaluator can interpret heterogeneous sets with duplicate doubles", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {function(a) { a }, 1, 3.14, 3.14, 5, 3.1415, 6, \"H\", 'c'};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{function(a) { a; }, 1, 3.14, 5, 6, \"H\", 'c'}");
  }

  TEST_CASE("The evaluator can interpret sets and grouped expressions", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1 + 2), (3 + 4)};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{3, 7}");
  }

  TEST_CASE("The evaluator can interpret simple sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 3.14, \"Hello\"};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 3.14, \"Hello\"}");
  }

  TEST_CASE("The evaluator can interpret nested sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]], {10, 11}};";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}}");
  }

  TEST_CASE("Sets can be iterated with range-based for loops", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "thisset := {\"apple\", \"banana\", \"cherry\"};"
      "y := {,};"
      "for x in thisset { y.append(x) }"
      "z := y;";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{\"apple\", \"banana\", \"cherry\"}");
    evaluator.Eval(parser.statements[1], environment);
    evaluator.Eval(parser.statements[2], environment);
    ObjectPtr y = evaluator.Eval(parser.statements[3], environment);
    REQUIRE(y->type == ObjectType::SET);
    REQUIRE(y->Inspect() == "{\"apple\", \"banana\", \"cherry\"}");
  }

} // namespace walnut