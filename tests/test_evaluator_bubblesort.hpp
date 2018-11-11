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

TEST_CASE("The evaluator can interpret bubblesort", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer =
      "bubble_sort := function(input) {"
      "  for current in range(length(input) - 1, 0, -1) {"
      "    for i in range(current) {"
      "      if input[i] > input[i + 1] {"
      "        temp: = input[i];"
      "        input[i] = input[i + 1];"
      "        input[i + 1] = temp;"
      "      }"
      "    }"
      "  }"
      "  return input;"
      "};"
      ""
      "[5, -4, 3, -2, 1].bubble_sort();";
  Lexer lexer(filename, buffer);
  lexer.Tokenize();
  Parser parser(lexer.tokens, buffer);
  parser.ParseProgram();
  Evaluator evaluator(buffer);
  ObjectPtr function = evaluator.Eval(parser.statements[0], environment);
  REQUIRE(function->type == ObjectType::FUNCTION);
  ObjectPtr result = evaluator.Eval(parser.statements[1], environment);
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[-4, -2, 1, 3, 5]");
}

} // namespace walnut