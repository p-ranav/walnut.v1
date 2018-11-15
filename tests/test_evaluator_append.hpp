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

  TEST_CASE("The evaluator can append to empty lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].append(1);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1]");
  }

  TEST_CASE("The evaluator can append to empty lists (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [,].append(3.14);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[3.14]");
  }

  TEST_CASE("The evaluator can append to single-valued lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [\"apples\",].append(\"oranges\");";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[\"apples\", \"oranges\"]");
  }

  TEST_CASE("The evaluator can interpret appending to character lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ['a', 'p', 'p', 'l', 'e', 's'].append('!');";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "['a', 'p', 'p', 'l', 'e', 's', '!']");
  }

  TEST_CASE("The evaluator can append grouped expressions to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1 + 2), (3 + 4)].append(5 + 6);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[3, 7, 11]");
  }

  TEST_CASE("The evaluator can append nested lists to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 3.14, \"Hello\"].append([4, 5]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 3.14, \"Hello\", [4, 5]]");
  }

  TEST_CASE("The evaluator can append nested sets to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]].append({10, 11});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}]");
  }

  TEST_CASE("The evaluator can append functions to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].append(function(a) { a; });";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[function(a) { a; }]");
  }

  TEST_CASE("The evaluator can append dictionaries to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].append({1:2, 3:4}).append({5:6, 7:8});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[{1 : 2, 3 : 4}, {5 : 6, 7 : 8}]");
  }

  TEST_CASE("The evaluator can append to empty sets (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.append(3.14);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{3.14}");
  }

  TEST_CASE("The evaluator can append to single-valued sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {\"apples\",}.append(\"oranges\");";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{\"apples\", \"oranges\"}");
  }

  TEST_CASE("The evaluator can interpret appending to character sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {'a', 'p', 'p', 'l', 'e', 's'}.append('!');";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{'a', 'p', 'l', 'e', 's', '!'}");
  }

  TEST_CASE("The evaluator can append grouped expressions to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1 + 2), (3 + 4)}.append(5 + 6);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{3, 7, 11}");
  }

  TEST_CASE("The evaluator can append nested lists to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 3.14, \"Hello\"}.append([4, 5]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 3.14, \"Hello\", [4, 5]}");
  }

  TEST_CASE("The evaluator can append nested sets to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]}.append({10, 11});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}}");
  }

  TEST_CASE("The evaluator can append functions to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.append(function(a) { a; });";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{function(a) { a; }}");
  }

  TEST_CASE("The evaluator can append dictionaries to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.append({1:2, 3:4}).append({5:6, 7:8});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{{1 : 2, 3 : 4}, {5 : 6, 7 : 8}}");
  }

  TEST_CASE("The evaluator can append to empty tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().append(1);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1)");
  }

  TEST_CASE("The evaluator can append to empty tuples (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (,).append(3.14);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(3.14)");
  }

  TEST_CASE("The evaluator can append to single-valued tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (\"apples\",).append(\"oranges\");";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(\"apples\", \"oranges\")");
  }

  TEST_CASE("The evaluator can interpret appending to character tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ('a', 'p', 'p', 'l', 'e', 's').append('!');";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "('a', 'p', 'p', 'l', 'e', 's', '!')");
  }

  TEST_CASE("The evaluator can append grouped expressions to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ((1 + 2), (3 + 4)).append(5 + 6);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(3, 7, 11)");
  }

  TEST_CASE("The evaluator can append nested lists to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (1, 3.14, \"Hello\").append([4, 5]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1, 3.14, \"Hello\", [4, 5])");
  }

  TEST_CASE("The evaluator can append nested sets to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ((1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]).append({10, 11});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "((1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11})");
  }

  TEST_CASE("The evaluator can append functions to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().append(function(a) { a; });";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(function(a) { a; })");
  }

  TEST_CASE("The evaluator can append dictionaries to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().append({1:2, 3:4}).append({5:6, 7:8});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "({1 : 2, 3 : 4}, {5 : 6, 7 : 8})");
  }

} // namespace walnut