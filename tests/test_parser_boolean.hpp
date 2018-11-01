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

  TEST_CASE("The parser can parse the boolean 'true;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "true;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::BOOLEAN);
    BooleanNodePtr boolean = std::dynamic_pointer_cast<BooleanNode>(parser.statements[0]);
    REQUIRE(boolean->ToString() == "true");
  }

  TEST_CASE("The parser can parse the boolean 'false;'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "false;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::BOOLEAN);
    BooleanNodePtr boolean = std::dynamic_pointer_cast<BooleanNode>(parser.statements[0]);
    REQUIRE(boolean->ToString() == "false");
  }

}