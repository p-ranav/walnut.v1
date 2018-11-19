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

  TEST_CASE("The parser can parse the call 'myfunction();'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "myfunction();";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::CALL_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "myfunction()");
    CallExpressionNodePtr call = std::dynamic_pointer_cast<CallExpressionNode>(parser.statements[0]);
    REQUIRE(call != nullptr);
    REQUIRE(call->arguments->elements.size() == 0);
  }

  TEST_CASE("The parser can parse the identity function 'myfunction(a);'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "myfunction(a);";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::CALL_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "myfunction(a)");
    CallExpressionNodePtr call = std::dynamic_pointer_cast<CallExpressionNode>(parser.statements[0]);
    REQUIRE(call != nullptr);
    REQUIRE(call->arguments->elements.size() == 1);
    REQUIRE(call->arguments->elements[0]->type == NodeType::IDENTIFIER);
  }

  TEST_CASE("The parser can parse the identity function 'myfunction(a = 1, b = 2);'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "myfunction(a = 1, b = 2);";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::CALL_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "myfunction(a = 1, b = 2)");
    CallExpressionNodePtr call = std::dynamic_pointer_cast<CallExpressionNode>(parser.statements[0]);
    REQUIRE(call != nullptr);
    REQUIRE(call->arguments->elements.size() == 2);
    REQUIRE(call->arguments->elements[0]->type == NodeType::KEY_VALUE_ARGUMENT);
    REQUIRE(call->arguments->elements[0]->type == NodeType::KEY_VALUE_ARGUMENT);
  }
  
  TEST_CASE("The parser can parse the identity function 'myfunction(a, b);'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "myfunction(a, b);";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::CALL_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "myfunction(a, b)");
    CallExpressionNodePtr call = std::dynamic_pointer_cast<CallExpressionNode>(parser.statements[0]);
    REQUIRE(call != nullptr);
    REQUIRE(call->arguments->elements.size() == 2);
    REQUIRE(call->arguments->elements[0]->type == NodeType::IDENTIFIER);
    REQUIRE(call->arguments->elements[1]->type == NodeType::IDENTIFIER);
  }

  TEST_CASE("The parser can parse the identity function 'myfunction(a, b, c = 1, d = 'w');'", "[parser]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = "myfunction(a, b, c = 1, d = 'w');";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    REQUIRE(parser.statements.size() == 1);
    REQUIRE(parser.statements[0]->type == Node::Type::CALL_EXPRESSION);
    REQUIRE(parser.statements[0]->ToString() == "myfunction(a, b, c = 1, d = 'w')");
    CallExpressionNodePtr call = std::dynamic_pointer_cast<CallExpressionNode>(parser.statements[0]);
    REQUIRE(call != nullptr);
    REQUIRE(call->arguments->elements.size() == 4);
    REQUIRE(call->arguments->elements[0]->type == NodeType::IDENTIFIER);
    REQUIRE(call->arguments->elements[1]->type == NodeType::IDENTIFIER);
    REQUIRE(call->arguments->elements[2]->type == NodeType::KEY_VALUE_ARGUMENT);
    REQUIRE(call->arguments->elements[3]->type == NodeType::KEY_VALUE_ARGUMENT);
  }
  
} // namespace walnut