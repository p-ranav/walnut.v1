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

TEST_CASE("The parser can parse the identifier 'foobar;'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::IDENTIFIER);
  IdentifierNodePtr identifier = std::dynamic_pointer_cast<IdentifierNode>(parser.statements[0]);
  REQUIRE(identifier->ToString() == "foobar");
}

TEST_CASE("The parser can parse the identifier 'foobar = 5'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = 5;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = 5");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::INTEGER);
  IntegerNodePtr integer_node = std::dynamic_pointer_cast<IntegerNode>(expression);
  REQUIRE(integer_node->value == 5);
}

TEST_CASE("The parser can parse the identifier 'foobar = 3.14'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = 3.14;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = 3.14");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::DOUBLE);
  DoubleNodePtr double_node = std::dynamic_pointer_cast<DoubleNode>(expression);
  REQUIRE(double_node->value == 3.14);
}

TEST_CASE("The parser can parse the identifier 'foobar = \"Hello\"'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = \"Hello\";";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = \"Hello\"");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::STRING_LITERAL);
  StringLiteralNodePtr string_node = std::dynamic_pointer_cast<StringLiteralNode>(expression);
  REQUIRE(string_node->value == "Hello");
}

TEST_CASE("The parser can parse the identifier 'foobar = 'a''", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = 'a';";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = 'a'");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::CHARACTER);
  CharacterNodePtr char_node = std::dynamic_pointer_cast<CharacterNode>(expression);
  REQUIRE(char_node->value == "a");
}

TEST_CASE("The parser can parse the identifier 'foobar = true'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = true;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = true");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::BOOLEAN);
  BooleanNodePtr boolean_node = std::dynamic_pointer_cast<BooleanNode>(expression);
  REQUIRE(boolean_node->value == true);
}

TEST_CASE("The parser can parse the identifier 'foobar = false'", "[parser]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = "foobar = false;";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  REQUIRE(parser.statements.size() == 1);
  REQUIRE(parser.statements[0]->type == Node::Type::VAR_STATEMENT);
  VarStatementNodePtr var_statement = std::dynamic_pointer_cast<VarStatementNode>(parser.statements[0]);
  REQUIRE(var_statement->ToString() == "foobar = false");
  IdentifierNodePtr identifier = var_statement->name;
  REQUIRE(identifier->value == "foobar");
  NodePtr expression = var_statement->expression;
  REQUIRE(expression->type == Node::Type::BOOLEAN);
  BooleanNodePtr boolean_node = std::dynamic_pointer_cast<BooleanNode>(expression);
  REQUIRE(boolean_node->value == false);
}

} // namespace walnut