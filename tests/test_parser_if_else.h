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

  TEST_CASE("The parser can parse the if expression 'if true {}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "if true {}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if true { }");
  }

  TEST_CASE("The parser can parse the if expression 'if true {} else {}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "if true {} else {}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if true { } else { }");
  }

  TEST_CASE("The parser can parse the if expression 'if false { return false; } else { return true; }'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "if false { return false; } else { return true; }";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if false { return false; } else { return true; }");
  }

  TEST_CASE("The parser can parse complex if-else expression 1", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = 
      "if (true and (true or false)) {"
          "print(\"Correctly inside if block\");"
      "}"
      "else {"
          "print(\"Wrongly inside else block\");"
      "}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if (true and (true or false)) { print(\"Correctly inside if block\"); } else { print(\"Wrongly inside else block\"); }");
  }

  TEST_CASE("The parser can parse complex if-else expression 2", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "if (false and (true or false)) {"
      "print(\"Correctly inside if block\");"
      "}"
      "else {"
      "print(\"Wrongly inside else block\");"
      "}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if (false and (true or false)) { print(\"Correctly inside if block\"); } else { print(\"Wrongly inside else block\"); }");
  }

  TEST_CASE("The parser can parse complex if-else expression 3", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "if x == 1 {} else if x == 2 {} else if x == 3 {} else {}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::IF_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "if (x == 1) { } else if (x == 2) { } else if (x == 3) { } else { }");
  }

}