#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

  TEST_CASE("Lexer can recognize the integer '0'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "0";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 2);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 1);
    REQUIRE(lexer.tokens[0].type == Token::Type::INTEGER);
    REQUIRE(lexer.tokens[0].value == "0");
    REQUIRE(lexer.tokens[1].file == "");
    REQUIRE(lexer.tokens[1].line == 1);
    REQUIRE(lexer.tokens[1].cursor == 2);
    REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[1].value == "EOF");
  }

  TEST_CASE("Lexer can recognize the integer '5'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "5";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 2);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 1);
    REQUIRE(lexer.tokens[0].type == Token::Type::INTEGER);
    REQUIRE(lexer.tokens[0].value == "5");
    REQUIRE(lexer.tokens[1].file == "");
    REQUIRE(lexer.tokens[1].line == 1);
    REQUIRE(lexer.tokens[1].cursor == 2);
    REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[1].value == "EOF");
  }

  TEST_CASE("Lexer can recognize the integer '42'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "42";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 2);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 1);
    REQUIRE(lexer.tokens[0].type == Token::Type::INTEGER);
    REQUIRE(lexer.tokens[0].value == "42");
    REQUIRE(lexer.tokens[1].file == "");
    REQUIRE(lexer.tokens[1].line == 1);
    REQUIRE(lexer.tokens[1].cursor == 3);
    REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[1].value == "EOF");
  }

  TEST_CASE("Lexer can recognize the integer '-96'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "-96";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 3);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 1);
    REQUIRE(lexer.tokens[0].type == Token::Type::SUBTRACTION_OPERATOR);
    REQUIRE(lexer.tokens[0].value == "-");
    REQUIRE(lexer.tokens[1].file == "");
    REQUIRE(lexer.tokens[1].line == 1);
    REQUIRE(lexer.tokens[1].cursor == 2);
    REQUIRE(lexer.tokens[1].type == Token::Type::INTEGER);
    REQUIRE(lexer.tokens[1].value == "96");
    REQUIRE(lexer.tokens[2].file == "");
    REQUIRE(lexer.tokens[2].line == 1);
    REQUIRE(lexer.tokens[2].cursor == 4);
    REQUIRE(lexer.tokens[2].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[2].value == "EOF");
  }

}