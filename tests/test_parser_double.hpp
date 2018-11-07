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

TEST_CASE("The parser can parse the double '2.71828;'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "2.71828;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::DOUBLE);
  DoubleNodePtr integer = std::dynamic_pointer_cast<DoubleNode>(parser.statements[0]);
  REQUIRE(integer->ToString() == "2.72");
}

} // namespace walnut