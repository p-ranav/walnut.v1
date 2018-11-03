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

  TEST_CASE("The evaluator can interpret '(1).type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "(1).type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::INTEGER);
  }

  TEST_CASE("The evaluator can interpret '(3.14).type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "(3.14).type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::DOUBLE);
  }

  TEST_CASE("The evaluator can interpret 'true.type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "true.type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::BOOLEAN);
  }

  TEST_CASE("The evaluator can interpret 'false.type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "false.type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::BOOLEAN);
  }

  TEST_CASE("The evaluator can interpret '\"\".type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "\"\".type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::STRING);
  }

  TEST_CASE("The evaluator can interpret '''.type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "''.type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::CHARACTER);
  }

  TEST_CASE("The evaluator can interpret '[].type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "[].type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::ARRAY);
  }

  TEST_CASE("The evaluator can interpret '{}.type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{}.type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::HASH);
  }

  TEST_CASE("The evaluator can interpret '{,}.type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{,}.type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::SET);
  }

  TEST_CASE("The evaluator can interpret '().type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "().type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::TUPLE);
  }

  TEST_CASE("The evaluator can interpret '(,).type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "(,).type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::TUPLE);
  }

  TEST_CASE("The evaluator can interpret '(1,).type()'", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "(1,).type()";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator;
    ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
    TypeObjectPtr result_type = std::dynamic_pointer_cast<TypeObject>(result);
    REQUIRE(result->type == ObjectType::TYPE);
    REQUIRE(result_type->value == ObjectType::TUPLE);
  }

}