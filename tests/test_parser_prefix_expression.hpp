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

  TEST_CASE("The parser can parse the prefix expression '!5;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "!5;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    PrefixExpressionNodePtr prefix = std::dynamic_pointer_cast<PrefixExpressionNode>(parser.statements[0]);
    REQUIRE(prefix->ToString() == "(!5)");
  }

  TEST_CASE("The parser can parse the prefix expression '-15;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "-15;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    PrefixExpressionNodePtr prefix = std::dynamic_pointer_cast<PrefixExpressionNode>(parser.statements[0]);
    REQUIRE(prefix->ToString() == "(-15)");
  }

  TEST_CASE("The parser can parse the prefix expression '!true;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "!true;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    PrefixExpressionNodePtr prefix = std::dynamic_pointer_cast<PrefixExpressionNode>(parser.statements[0]);
    REQUIRE(prefix->ToString() == "(!true)");
  }

  TEST_CASE("The parser can parse the prefix expression '!false;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "!false;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::PREFIX_EXPRESSION);
    PrefixExpressionNodePtr prefix = std::dynamic_pointer_cast<PrefixExpressionNode>(parser.statements[0]);
    REQUIRE(prefix->ToString() == "(!false)");
  }

}