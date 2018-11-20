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

TEST_CASE("The evaluator can interpret nested while statements", "[evaluator]")
{
  setlocale(LC_ALL, "");
  EnvironmentPtr environment = std::make_shared<Environment>();
  String filename = "";
  String buffer = 
    "nested_whiles := function(i, j, k) {"
    "i_done := false, j_done := false, k_done := false;"
    "while i < 10 {"
    "  if (i == 9) { i_done = true }"
    "  while j < 10 {"
    "    if (j == 9) { j_done = true }"
    "    while k < 10 {"
    "      if (k == 9) { k_done = true }"
    "      k = k + 1"
    "    }"
    "    j = j + 1"
    "  }"
    "  i = i + 1"
    "}"
    "return [i_done, j_done, k_done, \"OK\"];"
    "};"
    ""
    "i := 0, j := 0, k := 0;"
    "result: = nested_whiles(i, j, k);";

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
  REQUIRE(result->type == ObjectType::ARRAY);
  REQUIRE(result->Inspect() == "[true, true, true, \"OK\"]");
}

} // namespace walnut