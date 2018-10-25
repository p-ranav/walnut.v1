#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

TEST_CASE("The parser can parse the empty tuple '()'", "[lexer]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "()";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::TUPLE);
  REQUIRE(parser.statements[0]->ToString() == "()");
  TupleNodePtr tuple = std::dynamic_pointer_cast<TupleNode>(parser.statements[0]);
  REQUIRE(tuple->elements.size() == 0);
}