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

  TEST_CASE("The evaluator can interpret while expressions in variable declarations", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "i := 1;"
      "j := while i < 2000 { i = i * 2 }";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr i = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(i->type == ObjectType::INTEGER);
    REQUIRE(i->Inspect() == "1");
    ObjectPtr j = evaluator.Eval(parser.statements[1], environment);
    REQUIRE(j->type == ObjectType::INTEGER);
    REQUIRE(j->Inspect() == "2048");
  }

} // namespace walnut