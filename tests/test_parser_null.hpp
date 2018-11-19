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

  TEST_CASE("The parser can parse the null object", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "null;";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::NULL_);
    NullNodePtr null = std::dynamic_pointer_cast<NullNode>(parser.statements[0]);
    REQUIRE(null->ToString() == "null");
  }

} // namespace walnut