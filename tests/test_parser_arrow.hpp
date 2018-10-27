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

  TEST_CASE("The parser can parse the empty function '() => {}'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "() => {}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
    REQUIRE(parser.statements[0]->ToString() == "function() { }");
    FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
    REQUIRE(function->parameters.size() == 0);
  }

  TEST_CASE("The parser can parse the identity function 'a => a'", "[lexer]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "a => a";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
    REQUIRE(parser.statements[0]->ToString() == "function(a) { a; }");
    FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
    REQUIRE(function->parameters.size() == 1);
    REQUIRE(function->parameters[0]->value == "a");
    REQUIRE(function->body->statements.size() == 1);
    REQUIRE(function->body->statements[0]->ToString() == "a");
    REQUIRE(function->body->ToString() == "{ a; }");
  }

}