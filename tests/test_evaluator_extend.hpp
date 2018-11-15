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

  TEST_CASE("The evaluator can extend to empty lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].extend([1]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1]");
  }

  TEST_CASE("The evaluator can extend to empty lists (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [,].extend([3.14]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[3.14]");
  }

  TEST_CASE("The evaluator can extend to single-valued lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [\"apples\",].extend([\"oranges\"]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[\"apples\", \"oranges\"]");
  }

  TEST_CASE("The evaluator can interpret extending to character lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ['a', 'p', 'p', 'l', 'e', 's'].extend(['!']);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "['a', 'p', 'p', 'l', 'e', 's', '!']");
  }

  TEST_CASE("The evaluator can extend grouped expressions to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1 + 2), (3 + 4)].extend([5 + 6]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[3, 7, 11]");
  }

  TEST_CASE("The evaluator can extend nested lists to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [1, 3.14, \"Hello\"].extend([[4, 5]]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[1, 3.14, \"Hello\", [4, 5]]");
  }

  TEST_CASE("The evaluator can extend nested sets to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]].extend([{10, 11}]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}]");
  }

  TEST_CASE("The evaluator can extend functions to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].extend([function(a) { a; }]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[function(a) { a; }]");
  }

  TEST_CASE("The evaluator can extend dictionaries to lists", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := [].append({1:2, 3:4}).extend([{5:6, 7:8}]);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::ARRAY);
    REQUIRE(x->Inspect() == "[{1 : 2, 3 : 4}, {5 : 6, 7 : 8}]");
  }

  TEST_CASE("The evaluator can extend to empty sets (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.extend({3.14,});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{3.14}");
  }

  TEST_CASE("The evaluator can extend to single-valued sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {\"apples\",}.extend({\"oranges\",});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{\"apples\", \"oranges\"}");
  }

  TEST_CASE("The evaluator can interpret extending to character sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {'a', 'p', 'p', 'l', 'e', 's'}.extend({'!',});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{'a', 'p', 'l', 'e', 's', '!'}");
  }

  TEST_CASE("The evaluator can extend grouped expressions to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1 + 2), (3 + 4)}.extend({5 + 6,});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{3, 7, 11}");
  }

  TEST_CASE("The evaluator can extend nested lists to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {1, 3.14, \"Hello\"}.extend({[4, 5],});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{1, 3.14, \"Hello\", [4, 5]}");
  }

  TEST_CASE("The evaluator can extend nested sets to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {(1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]}.extend({{10, 11},});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{(1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11}}");
  }

  TEST_CASE("The evaluator can extend functions to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.extend({function(a) { a; },});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{function(a) { a; }}");
  }

  TEST_CASE("The evaluator can extend dictionaries to sets", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := {,}.append({1:2, 3:4}).extend({{5:6, 7:8},});";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::SET);
    REQUIRE(x->Inspect() == "{{1 : 2, 3 : 4}, {5 : 6, 7 : 8}}");
  }

  TEST_CASE("The evaluator can extend to empty tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().extend((1,));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1)");
  }

  TEST_CASE("The evaluator can extend to empty tuples (with comma)", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (,).extend((3.14,));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(3.14)");
  }

  TEST_CASE("The evaluator can extend to single-valued tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (\"apples\",).extend((\"oranges\",));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(\"apples\", \"oranges\")");
  }

  TEST_CASE("The evaluator can interpret extending to character tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ('a', 'p', 'p', 'l', 'e', 's').extend(('!',));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "('a', 'p', 'p', 'l', 'e', 's', '!')");
  }

  TEST_CASE("The evaluator can extend grouped expressions to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ((1 + 2), (3 + 4)).extend((5 + 6,));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(3, 7, 11)");
  }

  TEST_CASE("The evaluator can extend nested lists to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := (1, 3.14, \"Hello\").extend(([4, 5],));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(1, 3.14, \"Hello\", [4, 5])");
  }

  TEST_CASE("The evaluator can extend nested sets to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ((1, 2, 3), (4.0, 5.0, 6.0), (true, false),"
      "('W', 'n'), {\"a\": 5 }, [7, [8, 9]]).extend(({10, 11},));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "((1, 2, 3), (4.00, 5.00, 6.00), (true, false), ('W', 'n'), {\"a\" : 5}, [7, [8, 9]], {10, 11})");
  }

  TEST_CASE("The evaluator can extend functions to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().extend((function(a) { a; },));";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr x = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(x->type == ObjectType::TUPLE);
    REQUIRE(x->Inspect() == "(function(a) { a; })");
  }

  TEST_CASE("The evaluator can extend dictionaries to tuples", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "x := ().append({1:2, 3:4}).extend(({5:6, 7:8},));";

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