#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <test_lexer_keywords.hpp>
#include <test_lexer_punctuation.hpp>
#include <test_lexer_comments.hpp>
#include <test_lexer_integer.hpp>
#include <test_lexer_double.hpp>
#include <test_lexer_character.hpp>
#include <test_lexer_string.hpp>
#include <test_lexer_symbol.hpp>
#include <test_lexer_whitespace.hpp>

#include <test_parser_identifier.hpp>
#include <test_parser_integer.hpp>
#include <test_parser_double.hpp>
#include <test_parser_tuple.hpp>
#include <test_parser_set.hpp>
#include <test_parser_array.hpp>
#include <test_parser_arrow.hpp>
#include <test_parser_prefix_expression.hpp>
#include <test_parser_infix_expression.hpp>
#include <test_parser_operator_precedence.hpp>
#include <test_parser_grouped_expressions.hpp>
#include <test_parser_boolean.hpp> 

#include <test_evaluator_type.hpp>
#include <test_evaluator_split.hpp>
#include <test_evaluator_join.hpp>