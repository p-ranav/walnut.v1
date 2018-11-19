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

TEST_CASE("The parser can parse the empty function 'function() {}'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(){}";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function() { }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 0);
}

TEST_CASE("The parser can parse the identity function 'function(a) {a;}'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(a){a;}";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(a) { a; }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 1);
  REQUIRE(function->parameters[0]->type == NodeType::POSITIONAL_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(*args){ return args.length(); }'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(*args){ return args.length(); }";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(*args) { return length(args); }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 1);
  REQUIRE(function->parameters[0]->type == NodeType::VARIADIC_POSITIONAL_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(**kwargs){ return kwargs.keys(); }'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(**kwargs){ return kwargs.keys(); }";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(**kwargs) { return keys(kwargs); }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 1);
  REQUIRE(function->parameters[0]->type == NodeType::KEYWORD_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(a, b) {return a + b;}'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(a, b){return a + b;}";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(a, b) { return (a + b); }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 2);
  REQUIRE(function->parameters[0]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[1]->type == NodeType::POSITIONAL_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(a, b, *c) {return a + b;}'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(a, b, *c){return a + b;}";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(a, b, *c) { return (a + b); }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 3);
  REQUIRE(function->parameters[0]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[1]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[2]->type == NodeType::VARIADIC_POSITIONAL_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(a, b, *c, **d) {return true; }'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(a, b, *c, **d){return true; }";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(a, b, *c, **d) { return true; }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 4);
  REQUIRE(function->parameters[0]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[1]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[2]->type == NodeType::VARIADIC_POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[3]->type == NodeType::KEYWORD_PARAMETER);
}

TEST_CASE("The parser can parse the identity function 'function(a, b, **d) {return true; }'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "function(a, b, **d){return true; }";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::FUNCTION);
  REQUIRE(parser.statements[0]->ToString() == "function(a, b, **d) { return true; }");
  FunctionLiteralNodePtr function = std::dynamic_pointer_cast<FunctionLiteralNode>(parser.statements[0]);
  REQUIRE(function != nullptr);
  REQUIRE(function->parameters.size() == 3);
  REQUIRE(function->parameters[0]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[1]->type == NodeType::POSITIONAL_PARAMETER);
  REQUIRE(function->parameters[2]->type == NodeType::KEYWORD_PARAMETER);
}

} // namespace walnut