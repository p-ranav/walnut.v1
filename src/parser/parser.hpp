#pragma once
#include <token.hpp>
#include <node.hpp>
#include <integer_node.hpp>
#include <double_node.hpp>
#include <boolean_node.hpp>
#include <string_node.hpp>
#include <identifier_node.hpp>
#include <var_statement_node.hpp>
#include <return_statement_node.hpp>
#include <prefix_expression_node.hpp>
#include <if_expression_node.hpp>
#include <function_literal_node.hpp>
#include <call_expression_node.hpp>
#include <infix_expression_node.hpp>
#include <vector>
#include <map>
#include <memory>
#include <functional>

typedef std::vector<Token> TokenVector;
typedef const std::vector<Token> &TokenVectorConstRef;
typedef std::vector<std::shared_ptr<AstNode>> AstStatements;
typedef unsigned int UnsignedInt;
typedef Token::Type TokenType;
typedef std::function<AstNodePtr(void)> PrefixParseFunction;
typedef std::map<TokenType, std::function<AstNodePtr(void)>> PrefixParseFunctionMap;
typedef std::function<AstNodePtr(AstNodePtr)> InfixParseFunction;
typedef std::map<TokenType, std::function<AstNodePtr(AstNodePtr)>> InfixParseFunctionMap;

struct Parser
{
  explicit Parser(TokenVectorConstRef tokens);

  void ParseProgram();

  void NextToken();
  bool IsCurrentToken(TokenType value);
  bool IsPeekToken(TokenType value);
  bool ExpectPeek(TokenType value);

  AstNodePtr ParseStatement();
  AstNodePtr ParseVarStatement();
  AstNodePtr ParseReturnStatement();
  AstNodePtr ParseExpressionStatement();

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
    CALL         // my_function(X)
  };
  typedef std::map<TokenType, Precedence> TokenPrecedenceMap;

  Precedence PeekPrecedence();
  Precedence CurrentPrecedence();
  AstNodePtr ParseExpression(Precedence precedence);

  /* Prefix parse functions */
  AstNodePtr ParseIdentifier();
  AstNodePtr ParseInteger();
  AstNodePtr ParseDouble();
  AstNodePtr ParseBoolean();
  AstNodePtr ParsePrefixExpression();
  AstNodePtr ParseGroupedExpression();
  AstBlockStatementNodePtr ParseBlockStatement();
  AstNodePtr ParseIfExpression();
  std::vector<AstIdentifierNodePtr> ParseFunctionParameters();
  AstNodePtr ParseFunctionLiteral();

  /* Infix parse functions */
  AstNodePtr ParseInfixExpression(AstNodePtr left);
  std::vector<AstNodePtr> ParseCallArguments();
  AstNodePtr ParseCallExpression(AstNodePtr function);

  /* Member variables */
  TokenVector tokens;
  AstStatements statements;
  UnsignedInt current_token_index;
  Token current_token;
  Token peek_token;
  TokenPrecedenceMap precedences;
};