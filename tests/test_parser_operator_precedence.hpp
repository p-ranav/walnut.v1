#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

TEST_CASE("The parser can parse the expression '-a * b'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "-a * b;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "(-(a * b))");
}

TEST_CASE("The parser can parse the expression '!-a'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "!-a;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "(!(-a))");
}

TEST_CASE("The parser can parse the expression 'a + b + c'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a + b + c;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((a + b) + c)");
}

TEST_CASE("The parser can parse the expression 'a + b - c'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a + b - c;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((a + b) - c)");
}

TEST_CASE("The parser can parse the expression 'a * b * c'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a * b * c;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((a * b) * c)");
}

TEST_CASE("The parser can parse the expression 'a * b / c'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a * b / c;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((a * b) / c)");
}

TEST_CASE("The parser can parse the expression 'a + b / c'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a + b / c;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "(a + (b / c))");
}

TEST_CASE("The parser can parse the expression 'a + b * c + d / e - f'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "a + b * c + d / e - f;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "(((a + (b * c)) + (d / e)) - f)");
}

TEST_CASE("The parser can parse the expression '3 + 4; -5 * 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "3 + 4; -5 * 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 2);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "(3 + 4)");
  expression = parser.statements[1];
  REQUIRE(expression->ToString() == "(-(5 * 5))");
}

TEST_CASE("The parser can parse the expression '5 > 4 == 3 < 4'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 > 4 == 3 < 4;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((5 > 4) == (3 < 4))");
}

TEST_CASE("The parser can parse the expression '5 < 4 != 3 > 4'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 < 4 != 3 > 4;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((5 < 4) != (3 > 4))");
}

TEST_CASE("The parser can parse the expression '3 + 4 * 5 == 3 * 1 + 4 * 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "3 + 4 * 5 == 3 * 1 + 4 * 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  NodePtr expression = parser.statements[0];
  REQUIRE(expression->ToString() == "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))");
}

} // namespace walnut