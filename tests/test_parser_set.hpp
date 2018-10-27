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

  TEST_CASE("The parser can parse the empty set '{,}'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{,}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 0);
  }

  TEST_CASE("The parser can parse the set '{1,}'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{1,}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{1}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 1);
    for (auto& element : set->elements)
      REQUIRE(element->type == Node::Type::INTEGER);
    REQUIRE(set->elements[0]->ToString() == "1");
  }

}