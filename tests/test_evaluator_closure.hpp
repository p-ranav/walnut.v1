#pragma once
#include <catch.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <evaluator.hpp>
#include <environment.hpp>

#include <iostream>
#include <string>
#include <clocale>

namespace walnut
{

TEST_CASE("The evaluator can interpret closure", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
    "decorate : = function(f) {"
    "  wrapped_function: = function() {"
    "    result: = 1;"
    "    result = result + f();"
    "    result = result * 2;"
    "  };"
    "  return wrapped_function;"
    "};"
    ""
    "my_function: = function() { 5 }.decorate();"
    "result: = my_function();"
    ;

  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  for (auto& statement : parser.statements)
  {
    evaluator.Eval(statement, environment);
  }
  ObjectPtr result = environment->Get("result");
  REQUIRE(result != nullptr);
  REQUIRE(result->type == ObjectType::INTEGER);
  REQUIRE(result->Inspect() == "12");
}

} // namespace walnut