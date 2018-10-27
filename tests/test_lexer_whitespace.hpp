#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

  TEST_CASE("Lexer can recognize a single whitespace ' '", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = " ";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 1);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 2);
    REQUIRE(lexer.tokens[0].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[0].value == "EOF");
  }

  TEST_CASE("Lexer can recognize multiple whitespace characters '    '", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "    ";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    REQUIRE(lexer.tokens.size() == 1);
    REQUIRE(lexer.tokens[0].file == "");
    REQUIRE(lexer.tokens[0].line == 1);
    REQUIRE(lexer.tokens[0].cursor == 5);
    REQUIRE(lexer.tokens[0].type == Token::Type::END_OF_FILE);
    REQUIRE(lexer.tokens[0].value == "EOF");
  }

}