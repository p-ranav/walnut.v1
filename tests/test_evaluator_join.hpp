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

  TEST_CASE("The evaluator can interpret [\"Hello\", \"World\"].join(\" \")", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[\"Hello\", \"World\"].join(\" \")";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result->type == ObjectType::STRING);
    REQUIRE(result_string->Value() == "Hello World");
  }

  TEST_CASE("The evaluator can interpret [\"A\", \"B\", \"C\", \"D\"].join(\", \")", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[\"A\", \"B\", \"C\", \"D\"].join(\", \")";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result->type == ObjectType::STRING);
    REQUIRE(result_string->Value() == "A, B, C, D");
  }

  TEST_CASE("The evaluator can interpret [\"成功\", \"خيط\", \"தொடங்கியது\"].join(\"::\")", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[\"成功\", \"خيط\", \"தொடங்கியது\"].join(\"::\")";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result->type == ObjectType::STRING);
    REQUIRE(result_string->Value() == "成功::خيط::தொடங்கியது");
  }

  TEST_CASE("The evaluator can interpret [].join()", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[].join()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result->type == ObjectType::STRING);
    REQUIRE(result_string->Value() == "");
  }

  TEST_CASE("The evaluator can interpret [].join(\", \")", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[].join(\", \")";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result->type == ObjectType::STRING);
    REQUIRE(result_string->Value() == "");
  }

}