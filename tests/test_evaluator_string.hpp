#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

TEST_CASE("The evaluator can interpret \"Hello World\".split(\" \")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"Hello World\".split(\" \")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  String result_string = result->Inspect();
  REQUIRE(result->type == ObjectType::ARRAY);
  ArrayObjectPtr result_array = std::dynamic_pointer_cast<ArrayObject>(result);
  REQUIRE(result_array->elements.size() == 2);
  REQUIRE(result_array->elements[0]->type == ObjectType::STRING);
  REQUIRE(result_array->elements[1]->type == ObjectType::STRING);
  REQUIRE(result_string == "[\"Hello\", \"World\"]");
}

TEST_CASE("The evaluator can interpret \"A, B, C, D\".split(\", \")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"A, B, C, D\".split(\", \")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
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

TEST_CASE("The evaluator can interpret \"成功::خيط::தொடங்கியது\".split(\"::\")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"成功::خيط::தொடங்கியது\".split(\"::\")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
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

TEST_CASE("The evaluator can interpret [\"Hello\", \"World\"].join(\" \")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "[\"Hello\", \"World\"].join(\" \")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result->type == ObjectType::STRING);
  REQUIRE(result_string->Value() == "Hello World");
}

TEST_CASE("The evaluator can interpret [\"A\", \"B\", \"C\", \"D\"].join(\", \")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "[\"A\", \"B\", \"C\", \"D\"].join(\", \")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result->type == ObjectType::STRING);
  REQUIRE(result_string->Value() == "A, B, C, D");
}

TEST_CASE("The evaluator can interpret [\"成功\", \"خيط\", \"தொடங்கியது\"].join(\"::\")", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "[\"成功\", \"خيط\", \"தொடங்கியது\"].join(\"::\")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  Evaluator evaluator;
  ObjectPtr result = evaluator.Eval(parser.statements[0], environment);
  StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
  REQUIRE(result->type == ObjectType::STRING);
  REQUIRE(result_string->Value() == "成功::خيط::தொடங்கியது");
}