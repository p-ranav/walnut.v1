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

TEST_CASE("The parser can parse the empty tuple '()'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "();";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "()");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 0);
}

TEST_CASE("The parser can parse the empty tuple '(,)'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(,);";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "()");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 0);
}

TEST_CASE("The parser can parse this tuple '(1,)'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(1,);";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "(1)");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 1);
  for (auto &element : tuple->elements)
    REQUIRE(element->type == Node::Type::INTEGER);
  REQUIRE(tuple->elements[0]->ToString() == "1");
}

TEST_CASE("The parser can parse a tuple of integers '(1, 2, 3)'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(1, 2, 3);";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "(1, 2, 3)");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 3);
  for (auto &element : tuple->elements)
    REQUIRE(element->type == Node::Type::INTEGER);
  REQUIRE(tuple->elements[0]->ToString() == "1");
  REQUIRE(tuple->elements[1]->ToString() == "2");
  REQUIRE(tuple->elements[2]->ToString() == "3");
}

TEST_CASE("The parser can parse a tuple of doubles '(1.0, 2.5, 3.9)'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(1.0, 2.5, 3.9);";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "(1.00, 2.50, 3.90)");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 3);
  for (auto &element : tuple->elements)
    REQUIRE(element->type == Node::Type::DOUBLE);
  REQUIRE(tuple->elements[0]->ToString() == "1.00");
  REQUIRE(tuple->elements[1]->ToString() == "2.50");
  REQUIRE(tuple->elements[2]->ToString() == "3.90");
}

TEST_CASE("The parser can parse a tuple of strings '(\"x\", \"y\", \"z\")'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(\"x\", \"y\", \"z\");";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "(\"x\", \"y\", \"z\")");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 3);
  for (auto &element : tuple->elements)
    REQUIRE(element->type == Node::Type::STRING_LITERAL);
  REQUIRE(tuple->elements[0]->ToString() == "\"x\"");
  REQUIRE(tuple->elements[1]->ToString() == "\"y\"");
  REQUIRE(tuple->elements[2]->ToString() == "\"z\"");
}

TEST_CASE("The parser can parse the tuple '(1, 3.14, \"x\", true)'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "(1, 3.14, \"x\", true);";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "(1, 3.14, \"x\", true)");
  TupleNodePtr iterable = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(iterable->elements.size() == 4);
  REQUIRE(iterable->elements[0]->type == Node::Type::INTEGER);
  REQUIRE(iterable->elements[1]->type == Node::Type::DOUBLE);
  REQUIRE(iterable->elements[2]->type == Node::Type::STRING_LITERAL);
  REQUIRE(iterable->elements[3]->type == Node::Type::BOOLEAN);
  REQUIRE(iterable->elements[0]->ToString() == "1");
  REQUIRE(iterable->elements[1]->ToString() == "3.14");
  REQUIRE(iterable->elements[2]->ToString() == "\"x\"");
  REQUIRE(iterable->elements[3]->ToString() == "true");
}

} // namespace walnut