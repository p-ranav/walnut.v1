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

  TEST_CASE("The parser can parse the grouped expression '1 + (2 + 3) + 4'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "1 + (2 + 3) + 4";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
    NodePtr expression = parser.statements[0];
    REQUIRE(expression->ToString() == "((1 + (2 + 3)) + 4)");
  }

  TEST_CASE("The parser can parse the grouped expression '(5 + 5) * 2'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "(5 + 5) * 2";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
    NodePtr expression = parser.statements[0];
    REQUIRE(expression->ToString() == "((5 + 5) * 2)");
  }

  TEST_CASE("The parser can parse the grouped expression '2 / (5 + 5)'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "2 / (5 + 5)";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
    NodePtr expression = parser.statements[0];
    REQUIRE(expression->ToString() == "(2 / (5 + 5))");
  }

  TEST_CASE("The parser can parse the grouped expression '-(5 + 5)'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "-(5 + 5)";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    NodePtr expression = parser.statements[0];
    REQUIRE(expression->ToString() == "(-(5 + 5))");
  }

  TEST_CASE("The parser can parse the grouped expression '!(true == true)'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "!(true == true)";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    NodePtr expression = parser.statements[0];
    REQUIRE(expression->ToString() == "(!(true == true))");
  }

}