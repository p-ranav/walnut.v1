#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

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
}

TEST_CASE("Lexer can recognize the punctuation '>'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ">";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::GREATER_THAN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ">");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '<'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "<";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LESSER_THAN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "<");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '+'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "+";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::ADDITION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "+");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '-'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "-";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::SUBTRACTION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "-");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '*'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "*";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MULTIPLICATION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "*");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '/'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "/";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::DIVISION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "/");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '%'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "%";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MODULUS_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "%");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '('", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LEFT_PARENTHESIS);
  REQUIRE(lexer.tokens[0].value == "(");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '{'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "{";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LEFT_CURLY_BRACES);
  REQUIRE(lexer.tokens[0].value == "{");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '['", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "[";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LEFT_SQUARE_BRACKETS);
  REQUIRE(lexer.tokens[0].value == "[");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation ')'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ")";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::RIGHT_PARENTHESIS);
  REQUIRE(lexer.tokens[0].value == ")");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '}'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "}";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::RIGHT_CURLY_BRACES);
  REQUIRE(lexer.tokens[0].value == "}");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation ']'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "]";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::RIGHT_SQUARE_BRACKETS);
  REQUIRE(lexer.tokens[0].value == "]");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '&'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "&";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_AND_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "&");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '|'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "|";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_OR_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "|");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '^'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "^";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_XOR_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "^");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '~'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "~";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_ONES_COMPLEMENT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "~");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '!'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "!";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LOGICAL_NOT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "!");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::ASSIGNMENT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '＝'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "＝";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::ASSIGNMENT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "＝");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '≥'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "≥";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "≥");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '≤'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "≤";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "≤");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '≠'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "≠";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::INEQUALITY_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "≠");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '⋅'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "⋅";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MULTIPLICATION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "⋅");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '•'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "•";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MULTIPLICATION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "•");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '×'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "×";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MULTIPLICATION_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "×");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 2);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '=='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "==";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::EQUALITY_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "==");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '!='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "!=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::INEQUALITY_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "!=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '+='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "+=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::ADD_AND_ASSIGN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "+=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '-='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "-=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::SUBTRACT_AND_ASSIGN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "-=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '*='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "*=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MULTIPLY_AND_ASSIGN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "*=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '/='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "/=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::DIVIDE_AND_ASSIGN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "/=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '%='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "%=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::MODULUS_AND_ASSIGN_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "%=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '>='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ">=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::GREATER_THAN_OR_EQUAL_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ">=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '<='", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "<=";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LESSER_THAN_OR_EQUAL_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "<=");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '<<'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "<<";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_LEFT_SHIFT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "<<");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '>>'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = ">>";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::BITWISE_RIGHT_SHIFT_OPERATOR);
  REQUIRE(lexer.tokens[0].value == ">>");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '&&'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "&&";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LOGICAL_AND_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "and");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '||'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "||";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::LOGICAL_OR_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "or");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

TEST_CASE("Lexer can recognize the punctuation '=>'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "=>";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  REQUIRE(lexer.tokens.size() == 2);
  REQUIRE(lexer.tokens[0].file == "");
  REQUIRE(lexer.tokens[0].line == 1);
  REQUIRE(lexer.tokens[0].cursor == 1);
  REQUIRE(lexer.tokens[0].type == Token::Type::ARROW_OPERATOR);
  REQUIRE(lexer.tokens[0].value == "=>");
  REQUIRE(lexer.tokens[1].file == "");
  REQUIRE(lexer.tokens[1].line == 1);
  REQUIRE(lexer.tokens[1].cursor == 3);
  REQUIRE(lexer.tokens[1].type == Token::Type::END_OF_FILE);
  REQUIRE(lexer.tokens[1].value == "EOF");
}

} // namespace walnut