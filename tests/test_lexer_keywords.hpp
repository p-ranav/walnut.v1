#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

/*
    // Keywords
    KEYWORD_VAR,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,
    KEYWORD_FOR,
    KEYWORD_IN,
    KEYWORD_FUNCTION,
    KEYWORD_RETURN,
*/

TEST_CASE("Lexer can recognize the keyword 'true'", "[lexer]") 
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "true";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_TRUE);
  REQUIRE(lexer.tokens[0].value == "true");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 4);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'false'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "false";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_FALSE);
  REQUIRE(lexer.tokens[0].value == "false");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 5);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'if'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "if";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_IF);
  REQUIRE(lexer.tokens[0].value == "if");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'else'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "else";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_ELSE);
  REQUIRE(lexer.tokens[0].value == "else");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 4);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'while'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "while";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_WHILE);
  REQUIRE(lexer.tokens[0].value == "while");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 5);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'for'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "for";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_FOR);
  REQUIRE(lexer.tokens[0].value == "for");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'function'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_FUNCTION);
  REQUIRE(lexer.tokens[0].value == "function");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 8);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}

TEST_CASE("Lexer can recognize the keyword 'return'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "return";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 0);
  REQUIRE(lexer.tokens[0].type == Token::Type::KEYWORD_RETURN);
  REQUIRE(lexer.tokens[0].value == "return");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 6);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
  lexer.Tokenize();
}
