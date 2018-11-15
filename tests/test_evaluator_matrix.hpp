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

  TEST_CASE("The evaluator can interpret matrix transpose", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer =
      "Matrix : = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]];"
      ""
      "Matrixᵀ: = [];"
      "for i in range(4) {"
      "Rowᵀ: = [], for Row in Matrix{ Rowᵀ.append(Row[i]); }"
      "  Matrixᵀ.append(Rowᵀ);"
      "}"
      ""
      "// [[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]"
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
    ObjectPtr matrix = environment->Get("Matrix");
    REQUIRE(matrix->type == ObjectType::ARRAY);
    REQUIRE(matrix->Inspect() == "[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]");
    ObjectPtr transpose = environment->Get("Matrixᵀ");
    REQUIRE(transpose->type == ObjectType::ARRAY);
    REQUIRE(transpose->Inspect() == "[[1, 5, 9], [2, 6, 10], [3, 7, 11], [4, 8, 12]]");
  }

} // namespace walnut