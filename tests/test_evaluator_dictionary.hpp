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

TEST_CASE("The evaluator can interpret empty dictionary", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 0);
}

TEST_CASE("New keys can be added to an empty dictionary with [] operator", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {}; dict[1] = 2;";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 2}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
}

TEST_CASE("Existing key-value pairs can be updated with [] operator", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1 : 2}; dict[1] = 3;";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 3}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with int keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1: 2}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 2}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with double keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1.0: 2.0}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1.00 : 2.00}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<DoubleObject>(1.0))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with bool keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {true: 'Y'}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{true : 'Y'}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<BooleanObject>(true))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with char keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {'a': 'b'}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{'a' : 'b'}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<CharacterObject>("a"))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with string keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {\"sum\": function(a, b) { a + b }}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{\"sum\" : function(a, b) { (a + b); }}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<StringObject>("sum"))) != result_dict->pairs.end());
}

TEST_CASE("The evaluator can interpret dictionary with nested keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {\"a\": { 1 : { true : 'Y' } } }";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{\"a\" : {1 : {true : 'Y'}}}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<StringObject>("a"))) != result_dict->pairs.end());
}

TEST_CASE("Nested key-value pairs can be updated with [][]...[] operator", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {\"a\": { 1 : { true : 'Y' } } }; dict[\"a\"][1][true] = 'N';";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{\"a\" : {1 : {true : 'N'}}}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<StringObject>("a"))) != result_dict->pairs.end());
}

TEST_CASE("Walnut can check if a key exists in a dictionary with the 'in' operator", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1: 2}; exists := 1 in dict;";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 2}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
  ObjectPtr exists = environment->Get("exists");
  REQUIRE(exists != nullptr);
  REQUIRE(exists->type == ObjectType::BOOLEAN);
  REQUIRE(exists->Inspect() == "true");
}

TEST_CASE("Walnut can check if a key doesn't exist in a dictionary with the 'not in' operator", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1: 2}; exists := 3 not in dict;";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 2}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
  ObjectPtr exists = environment->Get("exists");
  REQUIRE(exists != nullptr);
  REQUIRE(exists->type == ObjectType::BOOLEAN);
  REQUIRE(exists->Inspect() == "true");
}

TEST_CASE("Walnut can check if a key doesn't exist in a dictionary with the 'not in' operator (II)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1: 2}; exists := 1 not in dict;";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{1 : 2}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<IntegerObject>(1))) != result_dict->pairs.end());
  ObjectPtr exists = environment->Get("exists");
  REQUIRE(exists != nullptr);
  REQUIRE(exists->type == ObjectType::BOOLEAN);
  REQUIRE(exists->Inspect() == "false");
}

TEST_CASE("UTF-8 characters can be keys", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {'世': \"Hah!\"};";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  REQUIRE(result->Inspect() == "{'世' : \"Hah!\"}");
  HashObjectPtr result_dict = std::dynamic_pointer_cast<HashObject>(result);
  REQUIRE(result_dict->pairs.size() == 1);
  REQUIRE(result_dict->pairs.find(Hash(std::make_shared<CharacterObject>("世"))) != result_dict->pairs.end());
}

TEST_CASE("Dictionaries can be iterated with for loops", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1 : 2, 3 : 4};"
    "result := 0;"
    "for pair in dict {"
    "  result = result + pair[0];"
    "}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  ObjectPtr key_sum = environment->Get("result");
  REQUIRE(key_sum != nullptr);
  REQUIRE(key_sum->type == ObjectType::INTEGER);
  REQUIRE(key_sum->Inspect() == "4");
}

TEST_CASE("Dictionaries can be iterated with for loops (kvpair)", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "dict := {1 : 2, 3 : 4};"
    "result := 0;"
    "for key, value in dict {"
    "    result = result + key + value;"
    "}";

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("dict");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::HASH);
  ObjectPtr key_sum = environment->Get("result");
  REQUIRE(key_sum != nullptr);
  REQUIRE(key_sum->type == ObjectType::INTEGER);
  REQUIRE(key_sum->Inspect() == "10");
}

} // namespace walnut