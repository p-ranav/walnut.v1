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

TEST_CASE("The parser can parse the infix expression '5 + 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 + 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 + 5)");
}

TEST_CASE("The parser can parse the infix expression '5 - 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 - 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 - 5)");
}

TEST_CASE("The parser can parse the infix expression '5 * 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 * 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 * 5)");
}

TEST_CASE("The parser can parse the infix expression '5 / 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 / 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 / 5)");
}

TEST_CASE("The parser can parse the infix expression '5 % 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 % 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 % 5)");
}

TEST_CASE("The parser can parse the infix expression '5 > 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 > 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 > 5)");
}

TEST_CASE("The parser can parse the infix expression '5 >= 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 >= 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 >= 5)");
}

TEST_CASE("The parser can parse the infix expression '5 < 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 < 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 < 5)");
}

TEST_CASE("The parser can parse the infix expression '5 <= 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 <= 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 <= 5)");
}

TEST_CASE("The parser can parse the infix expression '5 == 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 == 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 == 5)");
}

TEST_CASE("The parser can parse the infix expression '5 != 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "5 != 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(5 != 5)");
}

TEST_CASE("The parser can parse the infix expression 'true == true'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "true == true;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(true == true)");
}

TEST_CASE("The parser can parse the infix expression 'true != false'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "true != false;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(true != false)");
}

TEST_CASE("The parser can parse the infix expression 'false == false'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "false == false;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr infix = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(infix->ToString() == "(false == false)");
}

TEST_CASE("The parser can parse the boolean expression '3 < 5 == false'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "3 < 5 == false;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::INFIX_EXPRESSION);
  InfixExpressionNodePtr expression = std::dynamic_pointer_cast<InfixExpressionNode>(parser.statements[0]);
  REQUIRE(expression->ToString() == "((3 < 5) == false)");
}

} // namespace walnut