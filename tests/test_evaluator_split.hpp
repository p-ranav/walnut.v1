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

TEST_CASE("The evaluator can interpret \"\".split(\"\")", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"\".split(\"\");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 0);
  REQUIRE(result_string == "[]");
}

TEST_CASE("The evaluator can interpret \"\".split(\", \")", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"\".split(\", \");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 0);
  REQUIRE(result_string == "[]");
}

TEST_CASE("The evaluator can interpret \"Hello World\".split(\" \")", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"Hello World\".split(\" \");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 2);
  REQUIRE(result_array->elements[0]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[1]->type == ObjectType::STRING);
  REQUIRE(result_string == "[\"Hello\", \"World\"]");
}

TEST_CASE("The evaluator can interpret \"A, B, C, D\".split(\", \")", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"A, B, C, D\".split(\", \");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 4);
  REQUIRE(result_array->elements[0]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[1]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[2]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[3]->type == ObjectType::STRING);
  REQUIRE(result_string == "[\"A\", \"B\", \"C\", \"D\"]");
}

TEST_CASE("The evaluator can interpret \"成功::خيط::தொடங்கியது\".split(\"::\")", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"成功::خيط::தொடங்கியது\".split(\"::\");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 3);
  REQUIRE(result_array->elements[0]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[1]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[2]->type == ObjectType::STRING);
  REQUIRE(result_string == "[\"成功\", \"خيط\", \"தொடங்கியது\"]");
}

} // namespace walnut