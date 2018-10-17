#pragma once
#include <token.hpp>
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <string_literal_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <return_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <while_expression_node.h>
#include <function_literal_node.hpp>
#include <array_literal_node.hpp>
#include <index_expression_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <functional>

typedef std::vector<Token> TokenVector;
typedef const std::vector<Token> &TokenVectorConstRef;
typedef std::vector<NodePtr> Statements;
typedef unsigned int UnsignedInt;
typedef Token::Type TokenType;
typedef std::function<NodePtr(void)> PrefixParseFunction;
typedef std::map<TokenType, std::function<NodePtr(void)>> PrefixParseFunctionMap;
typedef std::function<NodePtr(NodePtr)> InfixParseFunction;
typedef std::map<TokenType, std::function<NodePtr(NodePtr)>> InfixParseFunctionMap;

struct Parser
{
  explicit Parser(TokenVectorConstRef tokens);

  void ParseProgram();

  void NextToken();
  bool IsCurrentToken(TokenType value);
  bool IsPeekToken(TokenType value);
  bool ExpectPeek(TokenType value);

  NodePtr ParseStatement();
  NodePtr ParseVarStatement();
  NodePtr ParseReturnStatement();
  NodePtr ParseExpressionStatement();

  PrefixParseFunctionMap prefix_parse_functions;
  void RegisterPrefixParseFunction(TokenType token, PrefixParseFunction function);

  InfixParseFunctionMap infix_parse_functions;
  void RegisterInfixParseFunction(TokenType token, InfixParseFunction function);

  enum Precedence
  {
    LOWEST,
    EQUAL,       // ==, !=
    LESSGREATER, // >, >=, < and <=
    SUM,         // +, -
    PRODUCT,     // *, /, %
    PREFIX,      // -X or !X
    CALL,        // my_function(X)
    INDEX,        // X[0], [1, 2, 3, 4][2]
    DOT
  };
  typedef std::map<TokenType, Precedence> TokenPrecedenceMap;

  Precedence PeekPrecedence();
  Precedence CurrentPrecedence();
  NodePtr ParseExpression(Precedence precedence, TokenType end = TokenType::SEMI_COLON_OPERATOR);

  /* Prefix parse functions */
  NodePtr ParseIdentifier();
  NodePtr ParseInteger();
  NodePtr ParseDouble();
  NodePtr ParseBoolean();
  NodePtr ParseStringLiteral();
  NodePtr ParsePrefixExpression();
  NodePtr ParseGroupedExpression();
  BlockStatementNodePtr ParseBlockStatement();
  NodePtr ParseIfExpression();
  NodePtr ParseWhileExpression();
  
  std::vector<IdentifierNodePtr> ParseFunctionParameters();
  NodePtr ParseFunctionLiteral();

  NodePtr ParseArrayLiteral();
  std::vector<NodePtr> ParseExpressionList(TokenType end);

  /* Infix parse functions */
  NodePtr ParseInfixExpression(NodePtr left);
  NodePtr ParseCallExpression(NodePtr function);
  NodePtr ParseIndexExpression(NodePtr left);
  NodePtr ParseDotOperator(NodePtr left);

  /* Member variables */
  TokenVector tokens;
  Statements statements;
  UnsignedInt current_token_index;
  Token current_token;
  Token peek_token;
  TokenPrecedenceMap precedences;
};