#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

TEST_CASE("Lexer can recognize the string '\"Hello World\"'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"Hello World\"";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::STRING_LITERAL);
  REQUIRE(lexer.tokens[0].value == "Hello World");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 14);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the string '\"Hello, 世界\"'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"Hello, 世界\"";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::STRING_LITERAL);
  REQUIRE(lexer.tokens[0].value == "Hello, 世界");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 12);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the string '\"ο Δίας\"'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "\"ο Δίας\"";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::STRING_LITERAL);
  REQUIRE(lexer.tokens[0].value == "ο Δίας");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 9);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}