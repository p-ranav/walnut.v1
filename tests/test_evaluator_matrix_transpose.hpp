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

  TEST_CASE("The evaluator can interpret matrix transpose operation", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "Matrix : = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]];"
      ""
      "Matrixᵀ: = [];"
      "for i in range(4) {"
      "  Rowᵀ: = [], for Row in Matrix{ Rowᵀ.append(Row[i]); }"
      "  Matrixᵀ.append(Rowᵀ);"
      "}"
      ""
      "Matrixᵀ;"
      "// [[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]];";
    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    ObjectPtr list = evaluator.Eval(parser.statements[0], environment);
    REQUIRE(list->type == ObjectType::ARRAY);
    REQUIRE(list->Inspect() == "[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]");
    ObjectPtr result_list = evaluator.Eval(parser.statements[1], environment);
    REQUIRE(result_list->type == ObjectType::ARRAY);
    REQUIRE(result_list->Inspect() == "[]");
    evaluator.Eval(parser.statements[2], environment);
    ObjectPtr final_result = evaluator.Eval(parser.statements[3], environment);
    REQUIRE(final_result->type == ObjectType::ARRAY);
    REQUIRE(final_result->Inspect() == "[[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]");
  }

} // namespace walnut