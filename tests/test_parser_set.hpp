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

  TEST_CASE("The parser can parse the empty set '{,}'", "[parser]")
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

  TEST_CASE("The parser can parse the set '{1,}'", "[parser]")
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

  TEST_CASE("The parser can parse a set of integers '{1, 2, 3}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{1, 2, 3}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{1, 2, 3}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 3);
    for (auto& element : set->elements)
      REQUIRE(element->type == Node::Type::INTEGER);
    REQUIRE(set->elements[0]->ToString() == "1");
    REQUIRE(set->elements[1]->ToString() == "2");
    REQUIRE(set->elements[2]->ToString() == "3");
  }

  TEST_CASE("The parser can parse a set of doubles '{1.0, 2.5, 3.9}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{1.0, 2.5, 3.9}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{1.00, 2.50, 3.90}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 3);
    for (auto& element : set->elements)
      REQUIRE(element->type == Node::Type::DOUBLE);
    REQUIRE(set->elements[0]->ToString() == "1.00");
    REQUIRE(set->elements[1]->ToString() == "2.50");
    REQUIRE(set->elements[2]->ToString() == "3.90");
  }

  TEST_CASE("The parser can parse a set of strings '{\"x\", \"y\", \"z\"}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{\"x\", \"y\", \"z\"}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{\"x\", \"y\", \"z\"}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 3);
    for (auto& element : set->elements)
      REQUIRE(element->type == Node::Type::STRING_LITERAL);
    REQUIRE(set->elements[0]->ToString() == "\"x\"");
    REQUIRE(set->elements[1]->ToString() == "\"y\"");
    REQUIRE(set->elements[2]->ToString() == "\"z\"");
  }

  TEST_CASE("The parser can parse a set of integers '{1, 2, 3, 3, 2, 1}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{1, 2, 3, 3, 2, 1}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    // yes, at the parser stage, duplicates are not removed
    // only at the evaluator stage is the property of a mathematical set maintained
    // this is because the set {a, 3} becomes {3} if a = 3 which I won't know
    // until evaluation
    REQUIRE(parser.statements[0]->ToString() == "{1, 2, 3, 3, 2, 1}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 6);
    for (auto& element : set->elements)
      REQUIRE(element->type == Node::Type::INTEGER);
    REQUIRE(set->elements[0]->ToString() == "1");
    REQUIRE(set->elements[1]->ToString() == "2");
    REQUIRE(set->elements[2]->ToString() == "3");
    REQUIRE(set->elements[3]->ToString() == "3");
    REQUIRE(set->elements[4]->ToString() == "2");
    REQUIRE(set->elements[5]->ToString() == "1");
  }

  TEST_CASE("The parser can parse the set '{1, 3.14, \"x\", true}'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "{1, 3.14, \"x\", true}";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::SET_LITERAL);
    REQUIRE(parser.statements[0]->ToString() == "{1, 3.14, \"x\", true}");
    SetLiteralNodePtr set = std::dynamic_pointer_cast<SetLiteralNode>(parser.statements[0]);
    REQUIRE(set->elements.size() == 4);
    REQUIRE(set->elements[0]->type == Node::Type::INTEGER);
    REQUIRE(set->elements[1]->type == Node::Type::DOUBLE);
    REQUIRE(set->elements[2]->type == Node::Type::STRING_LITERAL);
    REQUIRE(set->elements[3]->type == Node::Type::BOOLEAN);
    REQUIRE(set->elements[0]->ToString() == "1");
    REQUIRE(set->elements[1]->ToString() == "3.14");
    REQUIRE(set->elements[2]->ToString() == "\"x\"");
    REQUIRE(set->elements[3]->ToString() == "true");
  }

}