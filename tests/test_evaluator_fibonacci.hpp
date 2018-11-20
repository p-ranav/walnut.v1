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

  TEST_CASE("The evaluator can interpret fibonacci generator", "[evaluator]")
  {
    setlocale(LC_ALL, "");
    EnvironmentPtr environment = std::make_shared<Environment>();
    String filename = "";
    String buffer = 
      "fib : = function(n) {"
        "a: = 0, b : = 1, c : = 0; result := \"\";"
        "while (c < n) {"
      "  result = result + \"{0}\".format(c) + \" \";"
        "  c = (a + b), a = b, b = c;"
        "}"
        "return result;"
      "};"
      ""
      "fib_1000 := fib(1000);";

    Lexer lexer(filename, buffer);
    lexer.Tokenize();
    Parser parser(lexer.tokens, buffer);
    parser.ParseProgram();
    Evaluator evaluator(buffer);
    for (auto& statement : parser.statements)
    {
      evaluator.Eval(statement, environment);
    }
    ObjectPtr result = environment->Get("fib_1000");
    REQUIRE(result != nullptr);
    REQUIRE(result->type == ObjectType::STRING);
    StringObjectPtr result_string = std::dynamic_pointer_cast<StringObject>(result);
    REQUIRE(result_string->Value() == "0 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 ");
  }

} // namespace walnut