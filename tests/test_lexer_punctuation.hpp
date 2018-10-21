#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

TEST_CASE("Lexer can recognize the punctuation '.'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ".";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::DOT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ".");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the punctuation ','", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ",";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::COMMA_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ",");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the punctuation ':'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ":";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::COLON_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ":");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the punctuation ';'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ";";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::SEMI_COLON_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ";");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}