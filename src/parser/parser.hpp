#pragma once
#include <token.hpp>
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <character_node.hpp>
#include <string_literal_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <expression_assignment_statement_node.hpp>
#include <return_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <while_expression_node.hpp>
#include <for_expression_node.hpp>
#include <function_literal_node.hpp>
#include <positional_parameter_node.hpp>
#include <variadic_positional_parameters_node.hpp>
#include <keyword_parameters_node.hpp>
#include <array_literal_node.hpp>
#include <index_expression_node.hpp>
#include <hash_literal_node.hpp>
#include <set_literal_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>
#include <tuple_node.hpp>
#include <import_statement_node.hpp>
#include <key_value_argument_node.hpp>
#include <in_expression_node.hpp>
#include <null_node.hpp>
#include <break_statement_node.hpp>
#include <continue_statement_node.hpp>

#include <string.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace walnut
{

typedef std::vector<Token> TokenVector;
typedef const std::vector<Token> &TokenVectorConstRef;
typedef std::vector<NodePtr> Statements;
typedef unsigned int UnsignedInt;
typedef std::function<NodePtr(void)> PrefixParseFunction;
typedef std::map<Token::Type, std::function<NodePtr(void)>> PrefixParseFunctionMap;
typedef std::function<NodePtr(NodePtr)> InfixParseFunction;
typedef std::map<Token::Type, std::function<NodePtr(NodePtr)>> InfixParseFunctionMap;

struct Parser
{
  explicit Parser(TokenVectorConstRef tokens, StringConstRef buffer);

  void ParseProgram();

  void PreviousToken();
  void NextToken();
  bool IsCurrentToken(Token::Type value);
  bool IsPeekToken(Token::Type value);
  bool IsPeekTokenInList(const std::vector<Token::Type> &value);
  bool ExpectPeek(Token::Type value);
  unsigned int GetNumberOfDigits(unsigned int number);
  void ReportError(Token error_token, String brief_description, String detailed_description);

  NodePtr ParseStatement();
  NodePtr ParseVarStatement();
  NodePtr ParseAssignmentStatement();
  NodePtr ParseReturnStatement();
  NodePtr ParseImportStatement();
  NodePtr ParseExpressionStatement();
  NodePtr ParseBreakStatement();
  NodePtr ParseContinueStatement();

  PrefixParseFunctionMap prefix_parse_functions;
  void RegisterPrefixParseFunction(Token::Type token, PrefixParseFunction function);

  InfixParseFunctionMap infix_parse_functions;
  void RegisterInfixParseFunction(Token::Type token, InfixParseFunction function);

  enum Precedence
  {
    LOWEST,
    IF_ELSE,                 // if-else
    LOGICAL_OR,              // or
    LOGICAL_AND,             // and
    LOGICAL_NOT,             // not x
    EQUALITY,                // ==, !=
    COMPARISON,              // in, not in, <, <=, >, >=, ==
    ADDITION_SUBTRACTION,    // +, -
    MULTIPLICATION_DIVISION, // *, /, %
    NEGATION,                // -X
    ATTRIBUTE,               // x[0], [1, 2, 3, 4][2], x.y() and y(x)
  };
  typedef std::map<Token::Type, Precedence> TokenPrecedenceMap;

  Precedence PeekPrecedence();
  Precedence CurrentPrecedence();
  NodePtr ParseExpression(Precedence precedence,
                          const std::vector<Token::Type> &end =
                              {Token::Type::SEMI_COLON_OPERATOR, Token::Type::END_OF_FILE});

  /* Prefix parse functions */
  NodePtr ParseNull();
  NodePtr ParseIdentifier();
  NodePtr ParseInteger();
  NodePtr ParseDouble();
  NodePtr ParseBoolean();
  NodePtr ParseCharacter();
  NodePtr ParseStringLiteral();
  NodePtr ParsePrefixExpression();
  NodePtr ParseGroupedExpression();
  BlockStatementNodePtr ParseBlockStatement();
  NodePtr ParseIfExpression();
  NodePtr ParseWhileExpression();
  NodePtr ParseForExpression();
  NodePtr ParseInExpression(NodePtr left);

  std::vector<NodePtr> ParseFunctionParameters(bool& variadic_positional_arguments_encountered, bool& variadic_keyword_arguments_encountered);
  NodePtr ParseFunctionLiteral();

  NodePtr ParseArrayLiteral();
  NodePtr ParseExpressionList(Token::Type end);

  NodePtr ParseSetLiteral(NodePtr first, size_t start_index);
  NodePtr ParseHashLiteral();

  NodePtr ParseTuple(NodePtr first, size_t start_index);

  /* Infix parse functions */
  NodePtr ParseInfixExpression(NodePtr left);
  NodePtr ParseCallExpression(NodePtr function);
  NodePtr ParseIndexExpression(NodePtr left);
  NodePtr ParseDotOperator(NodePtr left);
  NodePtr ParseTernaryOperator(NodePtr left);
  NodePtr ParseKeyValueArgument(NodePtr left);

  /* Member variables */
  TokenVector tokens;
  String buffer;
  Statements statements;
  UnsignedInt current_token_index;
  Token current_token;
  Token peek_token;
  TokenPrecedenceMap precedences;
};

} // namespace walnut